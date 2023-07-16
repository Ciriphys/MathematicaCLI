#include "mthpch.h"

#include "Core/Lexer.h"

MVector<MLexiconToken> MLexer::GenerateTokens(MString equation)
{
	MVector<MLexiconToken> tokenArray = MVector<MLexiconToken>();
	MVector<MString> separetedEquation = SeparateString(equation);

	for (auto substring : separetedEquation)
	{
		ELexiconTokenType type = GetTypeFromSubstring(substring);
		switch (type)
		{
		case ELexiconTokenType::Number:
			tokenArray.emplace_back(Process(substring), type);
			break;
		default:
			tokenArray.emplace_back(substring, type);
			break;
		}
	}

	return tokenArray;
}

ELexiconTokenType MLexer::GetTypeFromSubstring(MString substring)
{
	// TO IMPLEMENT

	return ELexiconTokenType();
}

MVector<MString> MLexer::SeparateString(MString string, char separetor)
{
	MString currentSubstring = "";
	MVector<MString> result = MVector<MString>();

	for (char currentChar : string)
	{
		if (currentChar == separetor)
		{
			if (currentSubstring != "")
			{
				result.push_back(currentSubstring);
				currentSubstring = "";
			}
		}
		else
		{
			currentSubstring += currentChar;
		}
	}

	return result;
}

MString MLexer::Process(MString string)
{
	// TO IMPLEMENT

	return MString();
}
