#pragma once

#include "Utility/Utils.h"

namespace Mathematica
{
    namespace Integer
    {
        // Integer functions
        int32 LeastCommonMultiple(int32 a, int32 b);
        int32 GreatestCommonDivisor(int32 a, int32 b);

        // Prime numbers
        HashMap<int32, int32> Factorize(int32 n);
        bool IsPrime(int32 n);
        // Sieve of Erathosthenes
        Vector<int32> SoE (int32 max); 
    }
}