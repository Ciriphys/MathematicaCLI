#include "mthpch.h"

#include "Core/Number.h"
#include "Core/Parser.h"

#include "Utility/Utils.h"

MParser::MParser()
{
	mNodes = {};
}

void MParser::InitParser(const MVector<MLexiconToken>& tokens, const MHashMap<EPriority, MVector<int32>>& opIndexes)
{
	GenerateNodes(tokens);
	mOperationIndexes = opIndexes;
}

// NOTE : This function is deprecated, however it will be left here for a couple commit, until I decide what to do of it.
MRef<MMathNode> MParser::deprecated_GenerateTree()
{
	if (mNodes.size() == 0) return nullptr;

    MRef<MMathNode> root = nullptr;
	MVector<MLexiconToken> mRawTokens = {};

    for(auto token : mRawTokens)
    {
        MRef<MMathNode> currentToken = Mathematica::MakeRef<MMathNode>();

		switch (token.type)
		{
		case ELexiconTokenType::Number:
			currentToken->tokenData = MNumber(token.data);
			currentToken->type = EMathNodeType::Number;

			if (root)
			{
				root->children.push_back(currentToken);
				currentToken->parent = root;
			}
			else
			{
				root = currentToken;
			}
			break;

		case ELexiconTokenType::BinaryFunction:
			currentToken->tokenData = Mathematica::GetBinaryFunctionFromRawData(token.data);
			currentToken->type = EMathNodeType::BinaryFunction;

			if (root)
			{
				root->parent = currentToken;
				currentToken->children.push_back(root);

				if (root->type == EMathNodeType::BinaryFunction)
				{
					MTH_ASSERT(root->children.size() == 2, "Parser error: Binary function was not filled with both arguments.");
				}
			}

			root = currentToken;

			break;

		case ELexiconTokenType::Unknown:
			MTH_ASSERT(false, "Parser error: Unknown token found!");
			break;
		}
    }

	// Perform another check to make sure that even small incomplete inputs are caught.
	if (root->type == EMathNodeType::BinaryFunction)
	{
		MTH_ASSERT(root->children.size() == 2, "Parser error: Binary function was not filled with both arguments.");
	}

	mTree = root;
    return root;
}

void MParser::GenerateWrappedNodes(const MVector<int32>& indexes)
{
	for (auto index : indexes)
	{
		MRef<MMathNode> wrappedNode = mNodes[index];

		// Check if previous and next node are marked to be ignored and get the indexes for the left and right nodes.
		int32 leftCounter = 1;
		int32 rightCounter = 1;
		int32 copyIndex = index;
		while (mNodes[--copyIndex]->type == EMathNodeType::None) leftCounter++;
		copyIndex = index;
		while (mNodes[++copyIndex]->type == EMathNodeType::None) rightCounter++;

		// Instantiate a reference for these nodes
		MRef<MMathNode> leftNode = mNodes[index - leftCounter];
		MRef<MMathNode> rightNode = mNodes[index + rightCounter];

		// Make sure that the user sent a proper input.
		// Then, unwrap nodes and make links between parents and children.
		MTH_ASSERT(leftNode->type == EMathNodeType::Number || leftNode->type == EMathNodeType::Wrapper,
			"Parser error: tree generation cannot be completed, [leftNode] was not idoneous.");
		MTH_ASSERT(rightNode->type == EMathNodeType::Number || rightNode->type == EMathNodeType::Wrapper,
			"Parser error: tree generation cannot be completed, [rightNode] was not idoneous.");

		leftNode = (leftNode->type == EMathNodeType::Wrapper) ? leftNode->children.back() : leftNode;
		rightNode = (rightNode->type == EMathNodeType::Wrapper) ? rightNode->children.back() : rightNode;

		wrappedNode->children.push_back(leftNode);
		wrappedNode->children.push_back(rightNode);
		leftNode->parent = wrappedNode;
		rightNode->parent = wrappedNode;

		// Create a new wrapper node and append the wrapped tree. 
		// Then create new left and right nodes, and mark them to be ignored for the next calls.
		mNodes[index] = Mathematica::MakeRef<MMathNode>();
		mNodes[index]->type = EMathNodeType::Wrapper;
		mNodes[index]->children.push_back(wrappedNode);
		mNodes[index - leftCounter] = Mathematica::MakeRef<MMathNode>();
		mNodes[index + rightCounter] = Mathematica::MakeRef<MMathNode>();
		mNodes[index - leftCounter]->type = EMathNodeType::None;
		mNodes[index + rightCounter]->type = EMathNodeType::None;
	}
}

void MParser::GenerateNodes(const MVector<MLexiconToken>& tokens)
{
	for (auto token : tokens)
	{
		MRef<MMathNode> currentNode = Mathematica::MakeRef<MMathNode>();

		// Create node
		switch (token.type)
		{
		case ELexiconTokenType::Number:
			currentNode->tokenData = MNumber(token.data);
			currentNode->type = EMathNodeType::Number;
			break;
		case ELexiconTokenType::BinaryFunction:
			currentNode->tokenData = Mathematica::GetBinaryFunctionFromRawData(token.data);
			currentNode->type = EMathNodeType::BinaryFunction;
			break;
		default:
			MTH_ASSERT(false, "Parser error: Unkown token detected!");
			break;
		}

		mNodes.push_back(currentNode);
	}
}

MRef<MMathNode> MParser::GenerateTree()
{
	auto highIndexes = mOperationIndexes[EPriority::High];
	auto normalIndexes = mOperationIndexes[EPriority::Normal];
	auto lowIndexes = mOperationIndexes[EPriority::Low];

	GenerateWrappedNodes(highIndexes);
	GenerateWrappedNodes(normalIndexes);
	GenerateWrappedNodes(lowIndexes);

	for (auto node : mNodes)
	{
		if (node->type == EMathNodeType::Wrapper)
		{
			mTree = node->children.back();
			return mTree;
		}
	}

	return nullptr;
}
