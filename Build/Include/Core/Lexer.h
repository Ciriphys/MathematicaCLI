#pragma once

#include "Core/LexiconToken.h"

#include "Utility/Types.h"

enum class EPriority : int32
{
	Low, 
	Medium,
	High
};

class Lexer
{
public:
	Lexer();

	void GenerateTokens(String equation);

	Vector<LexiconToken> GetTokens() const { return mTokens; }
	Map<uint32, HashMap<EPriority, Vector<uint32>>> GetOperationIndex() const { return mOperationIndexes; }
	HashMap<uint32, Pair<uint32, Vector<Pair<uint32, uint32>>>> GetScopeCounter() const { return mScopeCounter; }

private:
	String StringifyNumberToken(String string, bool invertSign);

	Vector<LexiconToken> mTokens;
	Map<uint32, HashMap<EPriority, Vector<uint32>>> mOperationIndexes;
	HashMap<uint32, Pair<uint32, Vector<Pair<uint32, uint32>>>> mScopeCounter;
};

// NOTE : Making Lexer and Parser friends is potentially useful. Maybe in the future I'll change that.