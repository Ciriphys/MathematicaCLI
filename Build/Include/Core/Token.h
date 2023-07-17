#pragma once

#include "Utility/Utils.h"

enum class ELexiconTokenType : int
{
	Number,
	BinaryFunction,

	Unknown
};

struct MLexiconToken
{
	MString data;
	ELexiconTokenType type;

	MLexiconToken(MString __data, ELexiconTokenType __type);
	MString GetTokenRichInformation();

	bool operator== (MLexiconToken other)
	{
		return (data == other.data && type == other.type);
	}

	bool operator!= (MLexiconToken other)
	{
		return !(*this == other);
	}
};
