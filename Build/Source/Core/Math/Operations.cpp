#include "mthpch.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Integer.h"

#include "Core/Math/Number.h"

#include "Core/Utility/Types.h"

namespace Mathematica
{
    namespace Operation
    {
        Number Add(const Number& a, const Number& b)
        {
            int32 commonDenominator = Integer::LeastCommonMultiple(a.denominator, b.denominator);
            int32 numeratorA = a.numerator * commonDenominator / a.denominator;
            int32 numeratorB = b.numerator * commonDenominator / b.denominator;

            return { numeratorA + numeratorB, commonDenominator };
        }

        Number Subtract(const Number& a, const Number& b)
        {
            int32 commonDenominator = Integer::LeastCommonMultiple(a.denominator, b.denominator);
            int32 numeratorA = a.numerator * commonDenominator / a.denominator;
            int32 numeratorB = b.numerator * commonDenominator / b.denominator;

            return { numeratorA - numeratorB, commonDenominator };
        }

        Number Multiply(const Number& a, const Number& b)
        {
            int32 numerator = a.numerator * b.numerator;
            int32 denominator = a.denominator * b.denominator;
            
            return { numerator, denominator };
        }

        Number Divide(const Number& a, const Number& b)
        {
            int32 numerator = a.numerator * b.denominator;
            int32 denominator = a.denominator * b.numerator;
            
            MTH_ASSERT(denominator != 0, "DomainError: Cannot divide by zero!");

            return { numerator, denominator };
        }

        Number Mod(const Number& a, const Number& b)
        {
            // TODO : Implement Mod function.
            MTH_ASSERT(a.type != ENumberType::Integer || b.type != ENumberType::Integer, "Both numbers must be integers to perform Mod!");
            MTH_ASSERT(false, "Functionality not yet implemented!");

            return {};
        }
    }
}