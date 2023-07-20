#include "mthpch.h"

#include "Core/Math/Operations.h"

#include "Core/LexiconToken.h"
#include "Core/MathNode.h"
#include "Core/Number.h"

#include "Utility/Utils.h"

namespace Mathematica
{
	void Assert(const char* expression, const char* file, const char* function, int32 line, const char* message)
	{
		printf("Assertion failed (%s) in file %s,\nin function %s, at line %d:\n%s", expression, file, function, line, message);
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
		MTH_UNUSED(system("cls"));
#else
		MTH_UNUSED(system("clear"));
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

	MString Stringify(EMathNodeType type)
	{
		switch (type)
		{
		case EMathNodeType::Number:
			return "Number";
		case EMathNodeType::BinaryFunction:
			return "BinaryFunction";
		case EMathNodeType::Wrapper:
			return "Wrapper";
		default:
			return "Unknown";
		}
	}

	MString Stringify(MNumber number)
	{
		MStringStream stringStream;
		stringStream << number.numerator << "/" << number.denominator;

		return stringStream.str();
	}

	void DisplayParsedTree(const MRef<MMathNode>& node)
	{
		if (!node)
		{
			std::cout << "None" << std::endl;
			return;
		}

		for (auto child : node->children)
		{
			DisplayParsedTree(child);
		}

		MString data = "";

		try
		{
			data = Stringify(std::any_cast<MNumber>(node->tokenData));
		}
		catch (...)
		{
			auto function = std::any_cast<FBinaryFunction>(node->tokenData);
			data = Stringify(function);
		}

		std::cout << "Data : " << data << ", UUID: " << node->GetUUID() << " Type: " << Stringify(node->type) << ", parent: " << (node->parent ? node->parent->GetUUID() : "None") << std::endl;
		return;
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
		if (tokenArray.empty()) return;

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
		if (tokenArray.empty()) return;

		char endOfLine = bInline ? ' ' : '\n';
		auto lastToken = tokenArray.back();

		std::cout << "[" << endOfLine;
		for (auto token : tokenArray)
		{
			std::cout << token.GetUUID() << (token == lastToken ? "" : ",") << endOfLine;
		}
		std::cout << "]" << std::endl << std::endl;
	}

	int32 Max(int32 a, int32 b)
	{
		return a > b ? a : b;
	}

	int32 Min(int32 a, int32 b)
	{
		return a < b ? a : b;
	}

	// TODO : Fix return type
	FBinaryFunction GetBinaryFunctionFromRawData(const std::string& data)
	{
		if (data.size() == 1)
		{
			switch (data.front())
			{
			case '+': return &Mathematica::Operation::Add;
			case '-': return &Mathematica::Operation::Subtract;
			case '*': return &Mathematica::Operation::Multiply;
			case '/': return &Mathematica::Operation::Divide;
			}
		}

		MTH_ASSERT(false, "What kind of sorcery is this?!");
		return {};
	}

	MString Stringify(FBinaryFunction address)
	{
		FBinaryFunction addAddress		= &Mathematica::Operation::Add;
		FBinaryFunction subtractAddress = &Mathematica::Operation::Subtract;
		FBinaryFunction multiplyAddress = &Mathematica::Operation::Multiply;
		FBinaryFunction divideAddress	= &Mathematica::Operation::Divide;

		if		(address == addAddress)			return "Add";
		else if (address == subtractAddress)	return "Subtract";
		else if (address == multiplyAddress)	return "Multiply";
		else if (address == divideAddress)		return "Divide";

		MTH_ASSERT(false, "What kind of sorcery is this?!");
		return {};
	}

	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		b = a;
		a = temp;

		return;
	}
}