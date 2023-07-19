#pragma once

#include "Core/LexiconToken.h"
#include "Core/MathNode.h"

#include "Utility/Types.h"

class MParser
{
public:
    MParser(MVector<MLexiconToken> tokens);
    MRef<MMathNode> GenerateTree();

private: 
    MVector<MLexiconToken> mRawTokens;
    MRef<MMathNode> tree;
};