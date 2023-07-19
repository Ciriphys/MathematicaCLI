#include "mthpch.h"

#include "Utility/Utils.h"
#include "Core/Number.h"
#include "Core/Parser.h"

MParser::MParser()
{
	mRawTokens = {};
}

void MParser::InitParser(const MVector<MLexiconToken>& tokens)
{
	mRawTokens = tokens;
}

// TODO : Implement Wrapper nodes.
MRef<MMathNode> MParser::GenerateTree()
{
    MRef<MMathNode> root = nullptr;

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

	tree = root;
    return root;
}
