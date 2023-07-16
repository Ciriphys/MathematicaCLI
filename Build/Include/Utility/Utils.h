#pragma once

#include "Types.h"
#include <utility>
#include <stdio.h>
#include <stdlib.h>

#ifdef MTH_DEBUG 
    #define MTH_ASSERT(expression) if(!(expression)) Mathematica::Assert(#expression, Mathematica::RelativeToBuildPath(__FILE__).c_str(), __FUNCTION__, __LINE__)
#else 
    #define MTH_ASSERT(expression)
#endif

#ifdef MTH_WIN
    #define MTH_PROJECT_PATH "MathematicaCLI\\"
#else
    #define MTH_PROJECT_PATH "MathematicaCLI/"
#endif

#define MTH_VERSION "Version 0.0.1a"

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
    void Assert(const char* expression, const char* file, const char* function, int line);
    MString RelativeToBuildPath(MString file);

    // === Miscellaneous ===
    void ClearScreen();

    // === String manipulation ===
    // * The following functions are not locale-safe.
    // * This might change in the future.
    void TransformToLower(MString& string);
    void TransformToUpper(MString& string);

    // === Token ===
    void DisplayTokenArray(const MVector<MLexiconToken>& tokenArray, bool bInline = true);
    MString Stringify(ELexiconTokenType type);
};