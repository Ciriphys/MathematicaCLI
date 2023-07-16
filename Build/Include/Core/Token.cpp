#include "mthpch.h"

#include "Token.h"

MLexiconToken::MLexiconToken(MString __data, ELexiconTokenType __type) : data(__data), type(__type) {}

MString MLexiconToken::GetTokenRichInformation()
{
    MStringStream information;
    information << "@";
    information << Mathematica::Stringify(type);
    information << "(" << data << ")";

    return information.str();
}