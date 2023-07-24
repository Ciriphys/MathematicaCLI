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

    MMap<uint32, MVector<MRef<MMathNode>>> GetExecutionFlow() const { return mExecutionFlow; }

    MRef<MMathNode> GenerateTree();

private: 
    void GenerateWrappedNodes(MHashMap<EPriority, MVector<uint32>>& scopeData, EPriority priority);
    void GenerateNodes(const MVector<MLexiconToken>& tokens);

    MHashMap<uint32, MPair<uint32, MVector<MPair<uint32, uint32>>>> mScopeCounter;
    MMap<uint32, MHashMap<EPriority, MVector<uint32>>> mOperationIndexes;
    MVector<MRef<MMathNode>> mNodes;

    MMap<uint32, MVector<MRef<MMathNode>>> mExecutionFlow;

    MRef<MMathNode> mTree;

	uint32 mFirstIndex;
    uint32 mExecutionIndex;
};