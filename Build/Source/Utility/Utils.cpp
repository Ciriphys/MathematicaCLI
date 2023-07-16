#include "mthpch.h"

#include "Core/Token.h"
#include "Utility/Utils.h"

namespace Mathematica
{
	void Assert(const char* expression, const char* file, const char* function, int line)
	{
		printf("Assertion failed (%s) in file %s, in function %s, at line %d.", expression, file, function, line);
		abort();
	}

	MString RelativeToBuildPath(MString file)
	{
		MString path;
		MString prjPath = MTH_PROJECT_PATH;
		int index = file.find(prjPath) + prjPath.length();
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
			if ((int)c >= 65 && (int)c <= 90)
			{
				c += 32;
			}
		}
	}

	void TransformToUpper(MString& string)
	{
		for (auto& c : string)
		{
			if ((int)c >= 97 && (int)c <= 122)
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

	void DisplayTokenArray(const MVector<MLexiconToken>& tokenArray, bool bInline)
	{
		char endOfLine = bInline ? ' ' : '\n';

		std::cout << "[" << endOfLine;
		for (auto token : tokenArray)
		{
			std::cout << token.GetTokenRichInformation() << ',' << endOfLine;
		}
		std::cout << "]" << std::endl;
	}

}