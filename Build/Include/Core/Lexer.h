#pragma once

#include "Core/LexiconToken.h"

#include "Utility/Types.h"

enum class EPriority : int32
{
	Low, 
	Medium,
	High
};

class MLexer
{
public:
	MLexer();

	void GenerateTokens(MString equation);

	MVector<MLexiconToken> GetTokens() const { return mTokens; }
	MMap<uint32, MHashMap<EPriority, MVector<uint32>>> GetOperationIndex() const { return mOperationIndexes; }
	MHashMap<uint32, MPair<uint32, MVector<MPair<uint32, uint32>>>> GetScopeCounter() const { return mScopeCounter; }

private:
	MString StringifyNumberToken(MString string, bool invertSign);

	MVector<MLexiconToken> mTokens;
	MMap<uint32, MHashMap<EPriority, MVector<uint32>>> mOperationIndexes;
	MHashMap<uint32, MPair<uint32, MVector<MPair<uint32, uint32>>>> mScopeCounter;
};

// NOTE : Making MLexer and MParser friends is potentially useful. Maybe in the future I'll change that.