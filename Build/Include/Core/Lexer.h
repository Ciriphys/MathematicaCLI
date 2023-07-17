#pragma once

#include "Token.h"

class MLexer
{
public:
	MVector<MLexiconToken> GenerateTokens(MString equation);

private:
	MString RemoveTrailingZeros(MString string);
};

