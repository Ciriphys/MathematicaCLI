#include "mthpch.h"

#include "Core/Math/Integer.h"

#include "Utility/Utils.h"

namespace Mathematica
{
    namespace Integer
    {
        int32 LeastCommonMultiple(int32 a, int32 b)
        {   
            return a * b / GreatestCommonDivisor(a, b);
        }

        int32 GreatestCommonDivisor(int32 a, int32 b)
        {
            if(a == 0 || b == 0) return a == 0 ? b : a;
            if(a == b) return a;

            int32 greater = Mathematica::Max(a, b);
            int32 lower = Mathematica::Min(a, b);
            int32 remainder = greater % lower;

            while (remainder != 0)
            {
                greater = lower;
                lower = remainder;
                remainder = greater % lower;
            }
            
            return lower;
        }

		bool IsPrime(int32 n)
		{
            if (n < 2) return false;

            for (int32 i = 0; i * i < n; i++)
            {
                if (n % i == 0) return false;
            }

            return true;
		}

        MHashMap<int32, int32> Factorize(int32 n)
        {
            auto soe = SoE((int32)sqrt(n));
            MHashMap<int32, int32> result;

            for (int32 i = 0; i < soe.size(); i++)
            {
                int32 currentPrime = soe[i];

                if (n % currentPrime == 0)
                {
                    if (result.find(currentPrime) != result.end())
                    {
                        result[currentPrime]++;
                    }
                    else
                    {
                        result[currentPrime] = 1;
                    }

                    n /= currentPrime;
                    i--;
                }
            }

            if (result.empty())
            {
                result[n] = 1;
            }

            return result;
        }

        MVector<int32> SoE(int32 max)
        {
            // TODO : Implement a proper SoE and speed up the algorithm.
            MVector<int32> result;

            for (int32 i = 2; i <= max; i++)
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

// REFACTOR : Change C-like casts into C++-like casts.
