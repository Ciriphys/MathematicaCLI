#pragma once

#include "Core/LexiconToken.h"

#include "Core/Utility/Types.h"

enum class EPriority : Int32
{
	Low, 
	Medium,
	High,
	Macro
};

class Lexer
{
public:
	Lexer();

	void GenerateTokens(String equation);

	Vector<LexiconToken> GetTokens() const { return mTokens; }
	Map<UInt32, HashMap<EPriority, Vector<UInt32>>> GetOperationIndex() const { return mOperationIndexes; }
	HashMap<UInt32, Pair<UInt32, Vector<Pair<UInt32, UInt32>>>> GetScopeCounter() const { return mScopeCounter; }

private:
	String StringifyNumberToken(String string, bool invertSign);
	String PreliminaryProcess(String equation);

	Vector<LexiconToken> mTokens;

	// Token Metadata
	Map<UInt32, HashMap<EPriority, Vector<UInt32>>> mOperationIndexes;
	HashMap<UInt32, Pair<UInt32, Vector<Pair<UInt32, UInt32>>>> mScopeCounter;
	Map<UInt32, Pair<UInt32, String>> mFunctionMacros;
};

// NOTE : Making Lexer and Parser friends is potentially useful. Maybe in the future I'll change that.