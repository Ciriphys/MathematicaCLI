#pragma once

#include "Core/LexiconToken.h"
#include "Core/MathNode.h"
#include "Core/Lexer.h"

#include "Core/Utility/Types.h"

class Parser
{
public:
    Parser();

    void InitParser(const Vector<LexiconToken>& tokens, const Map<uint32, HashMap<EPriority, Vector<uint32>>>& opIndexes, const HashMap<uint32, Pair<uint32, Vector<Pair<uint32, uint32>>>>& scopeCounter);

    Map<uint32, Vector<Ref<MathNode>>> GetExecutionFlow() const { return mExecutionFlow; }

    Ref<MathNode> GenerateTree();

private: 
    void GenerateWrappedNodes(HashMap<EPriority, Vector<uint32>>& scopeData, EPriority priority);
    void GenerateNodes(const Vector<LexiconToken>& tokens);

    HashMap<uint32, Pair<uint32, Vector<Pair<uint32, uint32>>>> mScopeCounter;
    Map<uint32, HashMap<EPriority, Vector<uint32>>> mOperationIndexes;
    Vector<Ref<MathNode>> mNodes;

    Map<uint32, Vector<Ref<MathNode>>> mExecutionFlow;

    Ref<MathNode> mTree;

	uint32 mFirstIndex;
    uint32 mCurrentScope;
    uint32 mExecutionIndex;
};