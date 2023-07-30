#pragma once

#include "Core/Utility/Types.h"

#ifdef MTH_DEBUG 
#define MTH_ASSERT(expression, message) if(!(expression)) Mathematica::Assert(#expression, Mathematica::RelativeToBuildPath(__FILE__).c_str(), __FUNCTION__, __LINE__, message)
#define MTH_DEBUG_INFO(function) DisplayFunctionInfo(#function, __FUNCTION__); function
#else 
#define MTH_ASSERT(expression, message)
#define MTH_DEBUG_INFO(function) function;
#endif

#ifdef MTH_WIN
constexpr auto MTH_PROJECT_PATH = "MathematicaCLI\\";
#else
constexpr auto MTH_PROJECT_PATH = "MathematicaCLI/";

#ifndef __FUNCSIG__
#define __FUNCSIG__ __FUNCTION__
#endif

#endif

#define MTH_UNUSED(x) Mathematica::Cast<void>(x)
#define MTH_ADDRESS_OF(x) Mathematica::Recast<void*>(&x)
#define MTH_UINT_ADDRESS_OF(x) Mathematica::Recast<uint32*>MTH_ADDRESS_OF(x)

#define MTH_HIGH_WORD(x) Mathematica::Cast<uint8>((x >> 8) & MTH_WORD_MASK)	
#define MTH_LOW_WORD(x)	Mathematica::Cast<uint8>(x & MTH_WORD_MASK)
#define MTH_HIGH_DWORD(x) Mathematica::Cast<uint16>((x >> 16) & MTH_DWORD_MASK)
#define MTH_LOW_DWORD(x) Mathematica::Cast<uint16>(x & MTH_DWORD_MASK)
#define MTH_HIGH_QWORD(x) Mathematica::Cast<uint32>((x >> 32) & MTH_QWORD_MASK)
#define MTH_LOW_QWORD(x) Mathematica::Cast<uint32>(x & MTH_QWORD_MASK)

constexpr auto MTH_VERSION = "Version 0.0.13a";
constexpr auto MTH_NO_MESSAGE = "No message provided.";
constexpr auto MTH_FLOAT32_EPSILON = 1.192092896e-07F;

constexpr auto MTH_QWORD_MASK = 0xffffffff;
constexpr auto MTH_DWORD_MASK = 0xffff;
constexpr auto MTH_WORD_MASK = 0xff;

enum class ELexiconTokenType;
enum class EMathNodeType;

struct LexiconToken;
struct MathNode;

namespace Mathematica
{
	// === Smart pointers ===
	template<typename T, typename ... Args>
	constexpr Scope<T> MakeScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename ... Args>
	constexpr Ref<T> MakeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	// === Pair ===
	template <typename F, typename S>
	constexpr Pair<F, S> MakePair(F&& first, S&& second)
	{
		return std::make_pair<F, S>(std::forward<F>(first), std::forward<S>(second));
	}

	// === Any === 
	template <typename T>
	constexpr auto AnyCast(const Any& value)
	{
		return std::any_cast<T>(value);
	}

	// === Casts === 
	template <typename F, typename S>
	constexpr auto Cast(const S& what)
	{
		return static_cast<F>(what);
	}

	template <typename T>
	constexpr auto Recast(const void* what)
	{
		return reinterpret_cast<T>(what);
	}

	// === Debug and files ===
	void Assert(const char* expression, const char* file, const char* function, int32 line, const char* message);
	void DisplayFunctionInfo(const char* functionName, const char* callerFunction);
	String RelativeToBuildPath(String file);

	// === Miscellaneous ===
	void ClearScreen();
	// TODO : Add implementations for Number as well.
	int32 Max(int32 a, int32 b);
	int32 Min(int32 a, int32 b);
	uint32 Max(uint32 a, uint32 b);
	uint32 Min(uint32 a, uint32 b);

	template<typename T>
	void Swap(T& a, T& b);

	// === Functions ===
	FBinaryFunction GetBinaryFunctionFromRawData(const String& data);
	char   ToChar(FBinaryFunction address);
	String Stringify(FBinaryFunction address);

	// === String manipulation ===
	// * The following functions are not locale-safe.
	// * This might change in the future.
	void TransformToLower(String& string);
	void TransformToUpper(String& string);

	Vector<String> SeparateString(String string, char separetor = ' ');
	void Replace(String& string, char what, char with);
	void RemoveQuotes(String& string);

	// === Token ===
	void DisplayTokenArray(const Vector<LexiconToken>& tokenArray, bool bInline = true);
	void DisplayTokenUUID(const Vector<LexiconToken>& tokenArray, bool bInline = true);
	String Stringify(ELexiconTokenType type);

	// === Tree ===
	void DisplayParsedTree(const Ref<MathNode>& node);
	String Stringify(EMathNodeType type);
	String Stringify(RationalNumber number);
};