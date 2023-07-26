#pragma once

#include "Core/Identifiable.h"

#include "Core/Utility/Utils.h"

enum class ELexiconTokenType : int32
{
	Number,
	BinaryFunction,
	WrapperStart, 
	WrapperEnd,

	Unknown
};

struct LexiconToken : public Identifiable
{
	String data;
	ELexiconTokenType type;

	LexiconToken(String __data, ELexiconTokenType __type);
	String GetTokenRichInformation();
};
