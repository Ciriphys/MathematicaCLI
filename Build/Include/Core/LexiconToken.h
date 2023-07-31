#pragma once

#include "Core/Identifiable.h"

#include "Core/Utility/Utils.h"

enum class ELexiconTokenType : Int32
{
	Number,
	BinaryFunction,
	WrapperStart, 
	WrapperEnd,
	Macro,

	Unknown
};

struct LexiconToken : public Identifiable
{
	String data;
	ELexiconTokenType type;

	LexiconToken(String __data, ELexiconTokenType __type);
	String GetTokenRichInformation();
};
