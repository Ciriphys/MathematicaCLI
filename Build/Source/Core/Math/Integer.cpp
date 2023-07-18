#include "mthpch.h"

#include "Utility/Utils.h"
#include "Core/Math/Integer.h"

namespace Mathematica
{
    namespace Integers
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
    }
}