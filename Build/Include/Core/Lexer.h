#pragma once

#include "Core/LexiconToken.h"

#include "Utility/Types.h"

enum class EPriority : int32
{
	Low, 
	Normal,
	High
};

class MLexer
{
public:
	MLexer();

	void GenerateTokens(MString equation);

	MVector<MLexiconToken> GetTokens() const { return mTokens; }
	MHashMap<EPriority, MVector<int32>> GetOperationIndex() const { return mOperationIndexes; }

private:
	MString RemoveTrailingZeros(MString string);

	MVector<MLexiconToken> mTokens;
	MHashMap<EPriority, MVector<int32>> mOperationIndexes;
	// MStack<MPair<int32, int32>> mWrapperStack; <--- To add in next commit
};

// NOTE : Making MLexer and MParser friends is potentially useful. Maybe in the future I'll change that.