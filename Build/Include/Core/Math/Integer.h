#pragma once

#include "Core/Utility/Utils.h"

namespace Mathematica
{
    namespace Integer
    {
        // Integer functions
        Int32 LeastCommonMultiple(Int32 a, Int32 b);
        Int32 GreatestCommonDivisor(Int32 a, Int32 b);

        // Prime numbers
        Map<Int32, Int32> Factorize(Int32 n);
        Map<Int32, Int32> Factorize(RationalNumber n);

        bool IsPrime(Int32 n);
        bool IsPrime(RationalNumber n);

		Int32 Prime(Int32 n);
		Int32 Prime(RationalNumber n);

        // Sieve of Erathosthenes
        Vector<Int32> SoE (Int32 max); 
    }
}