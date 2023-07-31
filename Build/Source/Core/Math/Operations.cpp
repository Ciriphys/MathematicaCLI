#include "mthpch.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Integer.h"
#include "Core/Math/Number.h"

#include "Core/Utility/Profiler.h"
#include "Core/Utility/Types.h"

namespace Mathematica
{
    namespace Operation
    {
        RationalNumber Add(const RationalNumber& a, const RationalNumber& b)
        {
            MTH_PROFILE_FUNCTION();

            Int32 commonDenominator = Integer::LeastCommonMultiple(a.denominator, b.denominator);
            Int32 numeratorA = a.numerator * commonDenominator / a.denominator;
            Int32 numeratorB = b.numerator * commonDenominator / b.denominator;

            return { numeratorA + numeratorB, commonDenominator };
        }

        RationalNumber Subtract(const RationalNumber& a, const RationalNumber& b)
        {
            MTH_PROFILE_FUNCTION();

            Int32 commonDenominator = Integer::LeastCommonMultiple(a.denominator, b.denominator);
            Int32 numeratorA = a.numerator * commonDenominator / a.denominator;
            Int32 numeratorB = b.numerator * commonDenominator / b.denominator;

            return { numeratorA - numeratorB, commonDenominator };
        }

        RationalNumber Multiply(const RationalNumber& a, const RationalNumber& b)
        {
            MTH_PROFILE_FUNCTION();

            Int32 numerator = a.numerator * b.numerator;
            Int32 denominator = a.denominator * b.denominator;
            
            return { numerator, denominator };
        }

        RationalNumber Divide(const RationalNumber& a, const RationalNumber& b)
        {
            MTH_PROFILE_FUNCTION();

            Int32 numerator = a.numerator * b.denominator;
            Int32 denominator = a.denominator * b.numerator;
            
            MTH_ASSERT(denominator != 0, "DomainError: Cannot divide by zero!");

            return { numerator, denominator };
        }

        RationalNumber Mod(const RationalNumber& a, const RationalNumber& b)
        {
            MTH_PROFILE_FUNCTION();

            // TODO : Implement Mod function.
            MTH_ASSERT(a.type != ENumberType::Integer || b.type != ENumberType::Integer, "Both numbers must be integers to perform Mod!");
            MTH_ASSERT(false, "Functionality not yet implemented!");

            return {};
        }
    }
}