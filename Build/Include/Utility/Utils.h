#pragma once

#include "Types.h"
#include <utility>

#ifdef MTH_DEBUG 
#define MTH_ASSERT(expression, message) if(!(expression)) Mathematica::Assert(#expression, Mathematica::RelativeToBuildPath(__FILE__).c_str(), __FUNCTION__, __LINE__, message)
#define MTH_DEBUG_INFO(function) DisplayFunctionInfo(#function, __FUNCTION__); function
#else 
#define MTH_ASSERT(expression, message)
#define MTH_DEBUG_INFO(function)
#endif

#ifdef MTH_WIN
#define MTH_PROJECT_PATH "MathematicaCLI\\"
#else
#define MTH_PROJECT_PATH "MathematicaCLI/"
#endif

#define MTH_VERSION "Version 0.0.3a"
#define MTH_NO_MESSAGE "No message provided."

template<typename T, typename ... Args>
constexpr MScoped<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename ... Args>
constexpr MRef<T> MakeRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

enum class ELexiconTokenType;
struct MLexiconToken;

namespace Mathematica
{
	// === Debug and files ===
	void Assert(const char* expression, const char* file, const char* function, int32 line, const char* message);
	void DisplayFunctionInfo(const char* functionName, const char* callerFunction);
	MString RelativeToBuildPath(MString file);

	// === Miscellaneous ===
	void ClearScreen();

	// === String manipulation ===
	// * The following functions are not locale-safe.
	// * This might change in the future.
	void TransformToLower(MString& string);
	void TransformToUpper(MString& string);
	MVector<MString> SeparateString(MString string, char separetor = ' ');
	void RemoveQuotes(MString& string);

	// === Token ===
	void DisplayTokenArray(const MVector<MLexiconToken>& tokenArray, bool bInline = true);
	void DisplayTokenUUID(const MVector<MLexiconToken>& tokenArray, bool bInline = true);
	MString Stringify(ELexiconTokenType type);
};