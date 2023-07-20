#include "mthpch.h"

#include "Core/Lexer.h"

#include "Utility/Utils.h"

MLexer::MLexer() : mTokens({}), mOperationIndexes({}) {}

void MLexer::GenerateTokens(MString equation)
{
	mTokens = {};
	mOperationIndexes = {};

	Mathematica::RemoveQuotes(equation);
	MVector<MString> separetedEquation = Mathematica::SeparateString(equation);

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

	// TODO : Wrap the contents of "-/+ creation" into parentheses, to prevent miscalculations with OOO.
	for (auto substring : separetedEquation)
	{
		// Hint: if size is 1 then it may be an operation. 
		// TODO (late) : Change the for loop to match literal expressions.
		if (substring.size() == 1 && isAnOperation(substring.front()))
		{
			if (mTokens.size() == 0 || mTokens.back().type == ELexiconTokenType::BinaryFunction)
			{
				if (substring.front() == '+' || substring.front() == '-')
				{
					mTokens.emplace_back("0", ELexiconTokenType::Number);
				}
			}

			mTokens.emplace_back(substring, ELexiconTokenType::BinaryFunction);

			// Add index of operation.
			if (substring.front() == '+' || substring.front() == '-')
			{
				mOperationIndexes[EPriority::Low].push_back((int32)(mTokens.size() - 1));
			}
			else
			{
				mOperationIndexes[EPriority::Normal].push_back((int32)(mTokens.size() - 1));
			}

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
					mTokens.emplace_back(currentSubsubstring, ELexiconTokenType::Unknown);
					currentSubsubstring = "";
					bIsNumber = true;
				}
				currentSubsubstring += currentChar;
			}
			else if(isAnOperation(currentChar))
			{
				if (!currentSubsubstring.empty())
				{
					mTokens.emplace_back(RemoveTrailingZeros(currentSubsubstring), ELexiconTokenType::Number);
				}
				else
				{
					if (mTokens.size() == 0 || mTokens.back().type == ELexiconTokenType::BinaryFunction)
					{
						if (currentChar == '+' || currentChar == '-')
						{
							mTokens.emplace_back("0", ELexiconTokenType::Number);
						}
					}
				}

				mTokens.emplace_back(MString(1, currentChar), ELexiconTokenType::BinaryFunction);

				// Add index of operation.
				if (currentChar == '+' || currentChar == '-')
				{
					mOperationIndexes[EPriority::Low].push_back((int32)(mTokens.size() - 1));
				}
				else
				{
					mOperationIndexes[EPriority::Normal].push_back((int32)(mTokens.size() - 1));
				}

				currentSubsubstring = "";
			}
			else
			{
				if (!currentSubsubstring.empty() && bIsNumber)
				{
					mTokens.emplace_back(RemoveTrailingZeros(currentSubsubstring), ELexiconTokenType::Number);
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
				mTokens.emplace_back(RemoveTrailingZeros(currentSubsubstring), ELexiconTokenType::Number);
			}
			else
			{
				mTokens.emplace_back(currentSubsubstring, ELexiconTokenType::Unknown);
			}
		}
	}
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

// REFACTOR : Change C-like casts into C++-like casts.
