#include "mthpch.h"

#include "Core/Utility/Profiler.h"
#include "Core/Utility/Utils.h"
#include "Core/Utility/Timer.h"

#include "Core/Math/Number.h"

#include "Core/Parser.h"

Parser::Parser()
{
	mNodes = {};
	mFirstIndex = -1;
	mExecutionFlow = {};
	mExecutionIndex = 0;
}

void Parser::InitParser(const Vector<LexiconToken>& tokens, const Map<uint32, HashMap<EPriority, Vector<uint32>>>& opIndexes, const HashMap<uint32, Pair<uint32, Vector<Pair<uint32, uint32>>>>& scopeCounter)
{
	GenerateNodes(tokens);
	mOperationIndexes = opIndexes;
	mScopeCounter = scopeCounter;
}

// REFACTOR : Use bit masks for type to improve readability.
void Parser::GenerateWrappedNodes(HashMap<EPriority, Vector<uint32>>& scopeData, EPriority priority)
{
	MTH_PROFILE_FUNCTION();

	Vector<uint32> indexes = scopeData[priority];

	for (auto index : indexes)
	{
		Ref<MathNode> wrappedNode = mNodes[index];

		// Check if previous and next node are marked to be ignored and get the indexes for the left and right nodes.
		uint32 leftCounter = 1;
		uint32 rightCounter = 1;

		uint32 copyIndex = index - 1;
		while (
			mNodes[copyIndex]->type == EMathNodeType::None ||
			mNodes[copyIndex]->type == EMathNodeType::WrapEnd ||
			mNodes[copyIndex]->type == EMathNodeType::WrapStart
		)
		{
			MTH_ASSERT(copyIndex != 0, "ParserError: There is no [leftNode] of type: Number!");

			leftCounter++;
			copyIndex--;
		}

		copyIndex = index + 1;
		while (
			mNodes[copyIndex]->type == EMathNodeType::None ||
			mNodes[copyIndex]->type == EMathNodeType::WrapStart ||
			mNodes[copyIndex]->type == EMathNodeType::WrapEnd
		)
		{
			MTH_ASSERT(copyIndex != mNodes.size() - 1, "ParserError: There is no [rightNode] of type: Number!");

			rightCounter++;
			copyIndex++;
		}

		// Instantiate a reference for these nodes
		Ref<MathNode> leftNode = mNodes[index - leftCounter];
		Ref<MathNode> rightNode = mNodes[index + rightCounter];

		// Make sure that the user sent a proper input.
		// Then, unwrap nodes and make links between parents and children.
		MTH_ASSERT(leftNode->type == EMathNodeType::Number || leftNode->type == EMathNodeType::Wrapper,
			"ParserError: Tree generation cannot be completed, [leftNode] was not idoneous.");
		MTH_ASSERT(rightNode->type == EMathNodeType::Number || rightNode->type == EMathNodeType::Wrapper,
			"ParserError: Tree generation cannot be completed, [rightNode] was not idoneous.");

		leftNode = (leftNode->type == EMathNodeType::Wrapper) ? leftNode->children.back() : leftNode;
		rightNode = (rightNode->type == EMathNodeType::Wrapper) ? rightNode->children.back() : rightNode;

		wrappedNode->children.push_back(leftNode);
		wrappedNode->children.push_back(rightNode);
		wrappedNode->scope = mCurrentScope;
		leftNode->parent = wrappedNode;
		rightNode->parent = wrappedNode;

		// Create a new wrapper node and append the wrapped tree. 
		// Then create new left and right nodes, and mark them to be ignored for the next calls.
		mNodes[index] = Mathematica::MakeRef<MathNode>();
		mNodes[index]->type = EMathNodeType::Wrapper;
		mNodes[index]->children.push_back(wrappedNode);
		mNodes[index - leftCounter] = Mathematica::MakeRef<MathNode>();
		mNodes[index + rightCounter] = Mathematica::MakeRef<MathNode>();
		mNodes[index - leftCounter]->type = EMathNodeType::None;
		mNodes[index + rightCounter]->type = EMathNodeType::None;

		// TODO : Save using a flag that is determined by a user command.
		// Save the current operation in the execution flow.
		mExecutionFlow[mExecutionIndex].push_back(wrappedNode);

		// Save the lowest index to speed up the search. 
		mFirstIndex = Mathematica::Min(mFirstIndex, index);
	}

	mExecutionIndex++;
}

void Parser::GenerateNodes(const Vector<LexiconToken>& tokens)
{
	MTH_PROFILE_FUNCTION();

	for (auto token : tokens)
	{
		Ref<MathNode> currentNode = Mathematica::MakeRef<MathNode>();

		// Create node
		switch (token.type)
		{
		case ELexiconTokenType::Number:
			currentNode->data = RationalNumber(token.data);
			currentNode->type = EMathNodeType::Number;
			break;
		case ELexiconTokenType::BinaryFunction:
			currentNode->data = Mathematica::GetBinaryFunctionFromRawData(token.data);
			currentNode->type = EMathNodeType::BinaryFunction;
			break;
		case ELexiconTokenType::WrapperStart:
			currentNode->type = EMathNodeType::WrapStart;
			break;
		case ELexiconTokenType::WrapperEnd:
			currentNode->type = EMathNodeType::WrapEnd;
			break;
		default:
			MTH_ASSERT(false, "ParserError: Unkown token detected!");
			break;
		}

		mNodes.push_back(currentNode);
	}
}

Ref<MathNode> Parser::GenerateTree()
{
	MTH_PROFILE_FUNCTION();

	for (auto it = mOperationIndexes.rbegin(); it != mOperationIndexes.rend(); it++)
	{
		mCurrentScope = it->first;
		auto scopeData = it->second;

		GenerateWrappedNodes(scopeData, EPriority::High);
		GenerateWrappedNodes(scopeData, EPriority::Medium);
		GenerateWrappedNodes(scopeData, EPriority::Low);

		auto parenthesesIndexes = mScopeCounter[mCurrentScope].second;

		for (auto [first, second] : parenthesesIndexes)
		{
			mNodes[first]->type = EMathNodeType::None;
			mNodes[second]->type = EMathNodeType::None;
		}
	}

	for (auto node : mNodes)
	{
		if (node->type == EMathNodeType::Wrapper || node->type == EMathNodeType::Number)
		{
			if (node->type == EMathNodeType::Number) return mTree = node;
			else return mTree = node->children.back();
		}
	}

	return nullptr;
}
