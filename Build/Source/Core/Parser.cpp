#include "mthpch.h"

#include "Utility/Utils.h"
#include "Core/Number.h"
#include "Core/Parser.h"

MParser::MParser(MVector<MLexiconToken> tokens)
{
    mRawTokens = tokens;
}

MRef<MMathNode> MParser::GenerateTree()
{
    MRef<MMathNode> root = nullptr, currentToken;

    for(auto token : mRawTokens)
    {
        currentToken = Mathematica::MakeRef<MMathNode>();

        if(token.type == ELexiconTokenType::Number)
        {
            currentToken->tokenData = std::any_cast<MNumber>(token.data);
        }
    }

    return nullptr;
}
