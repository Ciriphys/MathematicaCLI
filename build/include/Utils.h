#pragma once

#include "Types.h"
#include <utility>
#include <stdio.h>
#include <stdlib.h>

#ifdef MTH_DEBUG 
        #define MTH_ASSERT(expression) if(!(expression)) Mathematica::__assert(#expression, __FILE__, __LINE__);
    #else 
        #define MTH_ASSERT(expression)
#endif

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
    void Assert(const char* expression, const char* file, int line)
    {
        printf("Assertion failed (%s) in file %s, at line %d.", expression, file, line);
        abort();
    }
};