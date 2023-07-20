#pragma once

#include "Core/LexiconToken.h"
#include "Core/MathNode.h"
#include "Core/Lexer.h"

#include "Utility/Types.h"

class MParser
{
public:
    MParser();

    void InitParser(const MVector<MLexiconToken>& tokens, const MHashMap<EPriority, MVector<int32>>& opIndexes);

    MRef<MMathNode> GenerateTree();

private: 
    MVector<MLexiconToken> mRawTokens;
    MHashMap<EPriority, MVector<int32>> mOperationIndexes;

    MRef<MMathNode> tree;
};