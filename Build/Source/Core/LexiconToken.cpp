#include "mthpch.h"

#include "Core/LexiconToken.h"

LexiconToken::LexiconToken(String __data, ELexiconTokenType __type) : data(__data), type(__type) {}

String LexiconToken::GetTokenRichInformation()
{
    StringStream information;
    information << "@";
    information << Mathematica::Stringify(type);
    information << "(" << data << ")";

    return information.str();
}