#pragma once

#include "Types.h"

#ifdef MTH_DEBUG 
#define MTH_ASSERT(expression, message) if(!(expression)) Mathematica::Assert(#expression, Mathematica::RelativeToBuildPath(__FILE__).c_str(), __FUNCTION__, __LINE__, message)
#define MTH_DEBUG_INFO(function) DisplayFunctionInfo(#function, __FUNCTION__); function
#else 
#define MTH_ASSERT(expression, message) throw message
#define MTH_DEBUG_INFO(function)
#endif

#ifdef MTH_WIN
#define MTH_PROJECT_PATH "MathematicaCLI\\"
#else
#define MTH_PROJECT_PATH "MathematicaCLI/"
#endif

#define MTH_VERSION "Version 0.0.5a"
#define MTH_NO_MESSAGE "No message provided."
#define MTH_UNUSED(x) (void)x
#define MTH_ADDRESS_OF(x) (void*)&x
#define MTH_UINT_ADDRESS_OF(x) *(uint32*)MTH_ADDRESS_OF(x)

enum class ELexiconTokenType;
enum class EMathNodeType;

struct MLexiconToken;
struct MMathNode;

namespace Mathematica
{
	// === Smart pointers ===
	template<typename T, typename ... Args>
	constexpr MScope<T> MakeScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename ... Args>
	constexpr MRef<T> MakeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	// === Pair ===
	template <typename F, typename S>
	constexpr MPair<F, S> MakePair(F&& first, S&& second)
	{
		return std::make_pair<F, S>(std::forward<F>(first), std::forward<S>(second));
	}

	// === Debug and files ===
	void Assert(const char* expression, const char* file, const char* function, int32 line, const char* message);
	void DisplayFunctionInfo(const char* functionName, const char* callerFunction);
	MString RelativeToBuildPath(MString file);

	// === Miscellaneous ===
	void ClearScreen();
	// TODO : Add implementations for MNumber as well.
	int32 Max(int32 a, int32 b);
	int32 Min(int32 a, int32 b);
	template<typename T>
	void Swap(T& a, T& b);

	// === Functions ===
	FBinaryFunction GetBinaryFunctionFromRawData(const std::string& data);
	MString Stringify(FBinaryFunction address);

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

	// === Tree ===
	void DisplayParsedTree(const MRef<MMathNode>& node);
	MString Stringify(EMathNodeType type);
	MString Stringify(MNumber number);
};