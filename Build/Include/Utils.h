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
};