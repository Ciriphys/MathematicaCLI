#pragma once

#include "Core/LexiconToken.h"
#include "Core/MathNode.h"
#include "Core/Lexer.h"

#include "Utility/Types.h"

class MParser
{
public:
    MParser();

    void InitParser(const MVector<MLexiconToken>& tokens, const MMap<uint32, MHashMap<EPriority, MVector<uint32>>>& opIndexes, const MHashMap<uint32, MPair<uint32, MVector<MPair<uint32, uint32>>>>& scopeCounter);

    MRef<MMathNode> GenerateTree();

private: 
    void GenerateWrappedNodes(const MVector<uint32>& indexes);
    void GenerateNodes(const MVector<MLexiconToken>& tokens);

    MHashMap<uint32, MPair<uint32, MVector<MPair<uint32, uint32>>>> mScopeCounter;
    MMap<uint32, MHashMap<EPriority, MVector<uint32>>> mOperationIndexes;
    MVector<MRef<MMathNode>> mNodes;

    MRef<MMathNode> mTree;

	uint32 mScopedIndex;
};