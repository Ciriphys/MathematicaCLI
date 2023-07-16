#pragma once

#include "Token.h"

class MLexer
{
public:
	MVector<MLexiconToken> GenerateTokens(MString equation);

private:
	ELexiconTokenType GetTypeFromSubstring(MString substring);
	MVector<MString> SeparateString(MString string, char separetor = ' ');
	MString Process(MString string);
};

