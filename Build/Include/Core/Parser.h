#pragma once

#include "Core/LexiconToken.h"
#include "Core/MathNode.h"
#include "Core/Lexer.h"

#include "Core/Utility/Types.h"

class Parser
{
public:
    Parser();

    void InitParser(const Vector<LexiconToken>& tokens, const Map<UInt32, HashMap<EPriority, Vector<UInt32>>>& opIndexes, const HashMap<UInt32, Pair<UInt32, Vector<Pair<UInt32, UInt32>>>>& scopeCounter);

    Map<UInt32, Vector<Ref<MathNode>>> GetExecutionFlow() const { return mExecutionFlow; }

    Ref<MathNode> GenerateTree();

private: 
    void GenerateWrappedNodes(HashMap<EPriority, Vector<UInt32>>& scopeData, EPriority priority);
    void WrapMacros(HashMap<EPriority, Vector<UInt32>>& scopeData);
    void GenerateNodes(const Vector<LexiconToken>& tokens);

    HashMap<UInt32, Pair<UInt32, Vector<Pair<UInt32, UInt32>>>> mScopeCounter;
    Map<UInt32, HashMap<EPriority, Vector<UInt32>>> mOperationIndexes;
    Vector<Ref<MathNode>> mNodes;

    Map<UInt32, Vector<Ref<MathNode>>> mExecutionFlow;

    Ref<MathNode> mTree;

	UInt32 mFirstIndex;
    UInt32 mCurrentScope;
    UInt32 mExecutionIndex;
};