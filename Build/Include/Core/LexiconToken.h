#pragma once

#include "Core/Identifiable.h"

#include "Utility/Utils.h"

enum class ELexiconTokenType : int32
{
	Number,
	BinaryFunction,
	WrapperStart, 
	WrapperEnd,

	Unknown
};

struct MLexiconToken : public IIdentifiable
{
	MString data;
	ELexiconTokenType type;

	MLexiconToken(MString __data, ELexiconTokenType __type);
	MString GetTokenRichInformation();
};
