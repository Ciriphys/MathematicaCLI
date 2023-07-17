#pragma once

#include "Core/Identifiable.h"
#include "Utility/Utils.h"

enum class ELexiconTokenType : int32
{
	Number,
	BinaryFunction,

	Unknown
};

struct MLexiconToken : public MIdentifiable
{
	MString data;
	ELexiconTokenType type;

	MLexiconToken(MString __data, ELexiconTokenType __type);
	MString GetTokenRichInformation();

	bool operator== (MLexiconToken other)
	{
		return GetUUID() == other.GetUUID();
	}

	bool operator!= (MLexiconToken other)
	{
		return !(*this == other);
	}
};
