#pragma once

#include "Utility/Utils.h"

enum class ELexiconTokenType : int
{
	Number,
	BinaryFunction,

	Unknown,

	None
};

struct MLexiconToken
{
	MString data;
	ELexiconTokenType type;

	MLexiconToken(MString __data, ELexiconTokenType __type);
	MString GetTokenRichInformation();
};
