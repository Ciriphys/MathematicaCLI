#include "mthpch.h"

#include "Core/Utility/Profiler.h"
#include "Core/Utility/Utils.h"

#include "Core/Math/Integer.h"
#include "Core/Math/Number.h"

namespace Mathematica
{
    namespace Integer
    {
        Int32 LeastCommonMultiple(Int32 a, Int32 b)
        {   
            MTH_PROFILE_FUNCTION();

            return a * b / GreatestCommonDivisor(a, b);
        }

        Int32 GreatestCommonDivisor(Int32 a, Int32 b)
        {
            MTH_PROFILE_FUNCTION();

            if(a == 0 || b == 0) return a == 0 ? b : a;
            if(a == b) return a;

            Int32 greater = Mathematica::Max(a, b);
            Int32 lower = Mathematica::Min(a, b);
            Int32 remainder = greater % lower;

            while (remainder != 0)
            {
                greater = lower;
                lower = remainder;
                remainder = greater % lower;
            }
            
            return lower;
        }

		bool IsPrime(Int32 n)
		{
            if (n < 2) return false;

            for (Int32 i = 2; i * i <= n; i++)
            {
                if (n % i == 0) return false;
            }

            return true;
		}

        bool IsPrime(RationalNumber n)
        {
			MTH_ASSERT(n.type == ENumberType::Integer, "DomainError: Cannot factorize a non-integer number!");
			return IsPrime(n.numerator);
        }

        Int32 Prime(Int32 n)
        {
			if (n < 2) return n;

			for (Int32 i = 2; i * i <= n; i++)
			{
				if (n % i == 0) return i;
			}

			return n;
        }

        Int32 Prime(RationalNumber n)
        {
			MTH_ASSERT(n.type == ENumberType::Integer, "DomainError: Cannot factorize a non-integer number!");
			return IsPrime(n.numerator);
        }

        Map<Int32, Int32> Factorize(Int32 n)
        {
            MTH_PROFILE_FUNCTION();
			
            Map<Int32, Int32> result;
            int primeFactor = Prime(n);

            while (primeFactor != n)
            {
                result[primeFactor] = result.find(primeFactor) != result.end() ? result[primeFactor] + 1 : 1;
                n /= primeFactor;
                primeFactor = Prime(n);
            }

            result[primeFactor] = result.find(primeFactor) != result.end() ? result[primeFactor] + 1 : 1;

            return result;
        }

        Map<Int32, Int32> Factorize(RationalNumber n)
        {
            MTH_ASSERT(n.type == ENumberType::Integer, "DomainError: Cannot factorize a non-integer number!");
            return Factorize(n.numerator);
        }

        Vector<Int32> SoE(Int32 max)
        {
            MTH_PROFILE_FUNCTION();

            // TODO : Implement a proper SoE and speed up the algorithm.
            Vector<Int32> result;

            for (Int32 i = 2; i <= max; i++)
            {
                if (IsPrime(i))
                {
                    result.push_back(i);
                }
            }

            return result;
        }
	}
}
