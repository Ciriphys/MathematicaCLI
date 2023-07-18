#include "mthpch.h"

#include "Utility/Types.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Integer.h"

namespace Mathematica
{
    namespace Operations
    {
        MNumber Add(const MNumber& a, const MNumber& b)
        {
            int32 commonDenominator = Integer::LeastCommonMultiple(a.denominator, b.denominator);
            int32 numeratorA = a.numerator * commonDenominator / a.denominator;
            int32 numeratorB = b.numerator * commonDenominator / b.denominator;

            MNumber result = {numeratorA + numeratorB, commonDenominator};
            return result.LowestTerms();
        }

        MNumber Subtract(const MNumber& a, const MNumber& b)
        {
            int32 commonDenominator = Integer::LeastCommonMultiple(a.denominator, b.denominator);
            int32 numeratorA = a.numerator * commonDenominator / a.denominator;
            int32 numeratorB = b.numerator * commonDenominator / b.denominator;

            MNumber result = {numeratorA - numeratorB, commonDenominator};
            return result.LowestTerms();
        }

        MNumber Multiply(const MNumber& a, const MNumber& b)
        {
            int32 numerator = a.numerator * b.numerator;
            int32 denominator = a.denominator * b.denominator;
            
            MNumber result = { numerator, denominator };
            return result.LowestTerms();
        }


        MNumber Divide(const MNumber& a, const MNumber& b)
        {
            int32 numerator = a.numerator * b.denominator;
            int32 denominator = a.denominator * b.numerator;
            
            MNumber result = { numerator, denominator };
            return result.LowestTerms();
        }

        MNumber Mod(const MNumber& a, const MNumber& b)
        {
            // TODO : Implement Mod function.
            MTH_ASSERT(a.type != ENumberType::Integer || b.type != ENumberType::Integer, "Both numbers must be integers to perform Mod!");
            MTH_ASSERT(false, "Functionality not yet implemented!");

            return {};
        }
    }
}