#include "mthpch.h"

#include "Core/Token.h"
#include "Utility/Utils.h"

namespace Mathematica
{
	void Assert(const char* expression, const char* file, const char* function, int32 line, const char* message)
	{
		printf("Assertion failed (%s) in file %s, in function %s, at line %d:\n %s", expression, file, function, line, message);
		abort();
	}

	void DisplayFunctionInfo(const char* functionName, const char* callerFunction)
	{
		printf("%s requested a debug information call for function \"%s\".\n", callerFunction, functionName);
	}

	MString RelativeToBuildPath(MString file)
	{
		MString path;
		MString prjPath = MTH_PROJECT_PATH;
		uint64 index = file.find(prjPath) + prjPath.length();
		path = file.substr(index);

		return path;
	}

	void ClearScreen()
	{
#ifdef MTH_WIN
		system("cls");
#else
		system("clear");
#endif
	}

	void TransformToLower(MString& string)
	{
		for (auto& c : string)
		{
			if ((int32)c >= 65 && (int32)c <= 90)
			{
				c += 32;
			}
		}
	}

	void TransformToUpper(MString& string)
	{
		for (auto& c : string)
		{
			if ((int32)c >= 97 && (int32)c <= 122)
			{
				c -= 32;
			}
		}
	}

	MString Stringify(ELexiconTokenType type)
	{
		switch (type)
		{
		case ELexiconTokenType::Number:
			return "Number";
		case ELexiconTokenType::BinaryFunction:
			return "BinaryFunction";
		default:
			return "Unknown";
		}
	}

	void RemoveQuotes(MString& string)
	{
		if (string.front() == '\"' && string.back() == '\"')
		{
			string = MString(string.begin() + 1, string.end() - 1);
		}
	}

	MVector<MString> SeparateString(MString string, char separetor)
	{
		// Append a separator character to allow last separated to be included.
		string += separetor;

		MString currentSubstring = "";
		MVector<MString> result = MVector<MString>();

		bool bIsInQuotes = false;
		MTH_ASSERT(separetor != '\"', "Cannot use <\"> as a separator!");

		for (char currentChar : string)
		{
			if (currentChar == separetor && !bIsInQuotes)
			{
				if (!currentSubstring.empty())
				{
					result.push_back(currentSubstring);
					currentSubstring = "";
				}
			}
			else
			{
				if (currentChar == '\"')
				{
					bIsInQuotes = !bIsInQuotes;
				}
				currentSubstring += currentChar;
			}
		}

		MTH_ASSERT(!bIsInQuotes, "Quotes not ended!");
		if (result.empty())
		{
			result.push_back(currentSubstring);
		}
		return result;
	}

	void DisplayTokenArray(const MVector<MLexiconToken>& tokenArray, bool bInline)
	{
		char endOfLine = bInline ? ' ' : '\n';
		auto lastToken = tokenArray.back();

		std::cout << "[" << endOfLine;
		for (auto token : tokenArray)
		{
			std::cout << token.GetTokenRichInformation() << (token == lastToken ? "" : ",") << endOfLine;
		}
		std::cout << "]" << std::endl << std::endl;
	}

	void DisplayTokenUUID(const MVector<MLexiconToken>& tokenArray, bool bInline /*= true*/)
	{
		char endOfLine = bInline ? ' ' : '\n';
		auto lastToken = tokenArray.back();

		std::cout << "[" << endOfLine;
		for (auto token : tokenArray)
		{
			std::cout << token.GetUUID() << (token == lastToken ? "" : ",") << endOfLine;
		}
		std::cout << "]" << std::endl << std::endl;
	}

}