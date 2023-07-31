#include "mthpch.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Number.h"

#include "Core/LexiconToken.h"
#include "Core/MathNode.h"

#include "Core/Utility/Utils.h"

namespace Mathematica
{
	void Assert(const char* expression, const char* file, const char* function, Int32 line, const char* message)
	{
		printf("Assertion failed (%s) in file %s,\nin function %s, at line %d:\n%s", expression, file, function, line, message);
		abort();
	}

	void DisplayFunctionInfo(const char* functionName, const char* callerFunction)
	{
		printf("%s requested a debug information call for function \"%s\".\n", callerFunction, functionName);
	}

	String RelativeToBuildPath(String file)
	{
		String path;
		String prjPath = MTH_PROJECT_PATH;
		UInt64 index = file.find(prjPath) + prjPath.length();
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

	void TransformToLower(String& string)
	{
		for (auto& c : string)
		{
			if ((Int32)c >= 65 && (Int32)c <= 90)
			{
				c += 32;
			}
		}
	}

	void TransformToUpper(String& string)
	{
		for (auto& c : string)
		{
			if ((Int32)c >= 97 && (Int32)c <= 122)
			{
				c -= 32;
			}
		}
	}

	bool IsLetter(char Char)
	{
		return (Char >= 0x41 && Char <= 0x5a) || (Char >= 0x61 && Char <= 0x7a);
	}

	bool FindAt(String string, String substr, UInt32 where)
	{
		if (where + substr.length() > string.length()) return false;
		for (UInt32 i = 0; i < substr.length(); i++) if (string[where + i] != substr[i]) return false;
		return true;
	}

	String Stringify(ELexiconTokenType type)
	{
		switch (type)
		{
		case ELexiconTokenType::Number:			return "Number";
		case ELexiconTokenType::BinaryFunction: return "BinaryFunction";
		case ELexiconTokenType::WrapperStart:	return "WrapperStart";
		case ELexiconTokenType::WrapperEnd:		return "WrapperEnd";

		default: return "Unknown";
		}
	}

	String Stringify(EMathNodeType type)
	{
		switch (type)
		{
		case EMathNodeType::Number:			return "Number";
		case EMathNodeType::BinaryFunction: return "BinaryFunction";
		case EMathNodeType::Wrapper:		return "Wrapper";

		default: return "Unknown";
		}
	}

	String Stringify(RationalNumber number)
	{
		StringStream stringStream;
		stringStream << number.numerator;

		if (number.denominator != 1)
		{
			stringStream << "/" << number.denominator;
		}

		return stringStream.str();
	}

	void DisplayParsedTree(const Ref<MathNode>& node)
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

		String data = "";

		try
		{
			data = Stringify(Mathematica::AnyCast<RationalNumber>(node->data));
		}
		catch (...)
		{
			auto function = Mathematica::AnyCast<FBinaryFunction>(node->data);
			data = Stringify(function);
		}

		std::cout << "Data : " << data << ", UUID: " << node->GetShortUUID() << " Type: " << Stringify(node->type) << ", parent: " << (node->parent ? node->parent->GetShortUUID() : "None") << std::endl;
		return;
	}

	void RemoveQuotes(String& string)
	{
		if (string.front() == '\"' && string.back() == '\"')
		{
			string = String(string.begin() + 1, string.end() - 1);
		}
	}

	Vector<String> SeparateString(String string, char separator)
	{
		// Append a separator character to allow last separated to be included.
		string += separator;

		String currentSubstring = "";
		Vector<String> result = Vector<String>();

		bool bIsInQuotes = false;
		MTH_ASSERT(separator != '\"', "SyntaxError: Cannot use <\"> as a separator!");

		for (char currentChar : string)
		{
			if (currentChar == separator && !bIsInQuotes)
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

		MTH_ASSERT(!bIsInQuotes, "SyntaxError: Quotes not ended!");
		if (result.empty())
		{
			result.push_back(currentSubstring);
		}
		return result;
	}

	void Replace(String& string, char what, char with)
	{
		for (char& character : string)
		{
			if (character == what)
			{
				character = with;
			}
		}
	}

	void DisplayTokenArray(const Vector<LexiconToken>& tokenArray, bool bInline)
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

	void DisplayTokenUUID(const Vector<LexiconToken>& tokenArray, bool bInline /*= true*/)
	{
		if (tokenArray.empty()) return;

		char endOfLine = bInline ? ' ' : '\n';
		auto lastToken = tokenArray.back();

		std::cout << "[" << endOfLine;
		for (auto token : tokenArray)
		{
			std::cout << token.GetShortUUID() << (token == lastToken ? "" : ",") << endOfLine;
		}
		std::cout << "]" << std::endl << std::endl;
	}

	Int32 Max(Int32 a, Int32 b)
	{
		return a > b ? a : b;
	}

	Int32 Min(Int32 a, Int32 b)
	{
		return a < b ? a : b;
	}

	UInt32 Max(UInt32 a, UInt32 b)
	{
		return a > b ? a : b;
	}

	UInt32 Min(UInt32 a, UInt32 b)
	{
		return a < b ? a : b;
	}

	FBinaryFunction GetBinaryFunctionFromRawData(const String& data)
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

	char ToChar(FBinaryFunction address)
	{
		FBinaryFunction addAddress = &Mathematica::Operation::Add;
		FBinaryFunction subtractAddress = &Mathematica::Operation::Subtract;
		FBinaryFunction multiplyAddress = &Mathematica::Operation::Multiply;
		FBinaryFunction divideAddress = &Mathematica::Operation::Divide;

		if (address == addAddress)				return '+';
		else if (address == subtractAddress)	return '-';
		else if (address == multiplyAddress)	return '*';
		else if (address == divideAddress)		return '/';

		MTH_ASSERT(false, "What kind of sorcery is this?!");
		return {};
	}

	String Stringify(FBinaryFunction address)
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