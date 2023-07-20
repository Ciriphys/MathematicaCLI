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
    void GenerateWrappedNodes(const MVector<int32>& indexes);
    void GenerateNodes(const MVector<MLexiconToken>& tokens);

    [[deprecated]] MRef<MMathNode> deprecated_GenerateTree();

    MHashMap<EPriority, MVector<int32>> mOperationIndexes;
    MVector<MRef<MMathNode>> mNodes;

    MRef<MMathNode> mTree;
};