#include "mthpch.h"

#include "Core/Lexer.h"
#include "Utility/Utils.h"

MVector<MLexiconToken> MLexer::GenerateTokens(MString equation)
{
	MVector<MLexiconToken> tokenArray = MVector<MLexiconToken>();

	Mathematica::RemoveQuotes(equation);
	MVector<MString> separetedEquation = Mathematica::SeparateString(equation);

	for (auto substring : separetedEquation)
	{
		const char operations[] = { '+', '-', '*', '/' };
		auto isAnOperation = [operations](const char c) -> bool
		{
			for (int32 i = 0; i < 4; i++)
			{
				if (c == operations[i])
				{
					return true;
				}
			}

			return false;
		};

		// Hint32: if size is 1 then it may be an operation. 
		// TODO (late) : Change the for loop to match literal expressions 
		if (substring.size() == 1 && isAnOperation(substring.front()))
		{
			tokenArray.emplace_back(substring, ELexiconTokenType::BinaryFunction);
			continue;
		}

		// Check if a substring contains both numbers and operations.
		bool bIsNumber = true;
		MString currentSubsubstring = "";
		for (auto currentChar : substring)
		{
			if (!(currentChar < 48 || currentChar > 57)) // <-- Check if it is a number
			{
				if (!bIsNumber)
				{
					tokenArray.emplace_back(currentSubsubstring, ELexiconTokenType::Unknown);
					currentSubsubstring = "";
					bIsNumber = true;
				}
				currentSubsubstring += currentChar;
			}
			else if(isAnOperation(currentChar))
			{
				if (!currentSubsubstring.empty())
				{
					tokenArray.emplace_back(RemoveTrailingZeros(currentSubsubstring), ELexiconTokenType::Number);
				}
				tokenArray.emplace_back(MString(1, currentChar), ELexiconTokenType::BinaryFunction);
				currentSubsubstring = "";
			}
			else
			{
				if (!currentSubsubstring.empty() && bIsNumber)
				{
					tokenArray.emplace_back(RemoveTrailingZeros(currentSubsubstring), ELexiconTokenType::Number);
					currentSubsubstring = "";
				}
				currentSubsubstring += currentChar;
				bIsNumber = false;
			}
		}

		if (!currentSubsubstring.empty())
		{
			if (bIsNumber)
			{
				tokenArray.emplace_back(RemoveTrailingZeros(currentSubsubstring), ELexiconTokenType::Number);
			}
			else
			{
				tokenArray.emplace_back(currentSubsubstring, ELexiconTokenType::Unknown);
			}
		}
	}

	return tokenArray;
}

MString MLexer::RemoveTrailingZeros(MString string)
{
	bool bSkip = false;
	MString number = "";
	for (auto digit : string)
	{
		if (digit == '0' && !bSkip)
		{
			continue;
		}
		else
		{
			if (!bSkip)
			{
				bSkip = true;
			}
			number += digit;
		}
	}

	return number.length() > 0 ? number : "0";
}
