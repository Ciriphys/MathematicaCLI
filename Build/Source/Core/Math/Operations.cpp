#include "mthpch.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Rational.h"
#include "Core/Math/Integer.h"
#include "Core/Math/Number.h"

#include "Core/Utility/Profiler.h"

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

        RealNumber Exponentiate(const RationalNumber& a, RationalNumber b)
        {
            MTH_PROFILE_FUNCTION();
            MTH_ASSERT(b.denominator % 2 != 0 || Mathematica::Sign(a) == 1, "DomainError: Cannot compute an even-indexed root on a negative number!");

			RealNumber result = {};

            RationalNumber integer  = Mathematica::Cast<Int32>(b.RawNumerical());
            RationalNumber fraction = b - integer;

			result.rational = Raise(a, integer.numerator);

            // NOTE : Keep an eye on this check, maybe it is necessary to perform the check with the full fraction.
			if (!Mathematica::Rational::IsRootRational(a, b.denominator))
			{
                Ref<MathNode> operation = Mathematica::MakeRef<MathNode>();
                operation->data = "Raise";
                operation->type = EMathNodeType::NamedFunction;

                Ref<MathNode> arg = Mathematica::MakeRef<MathNode>();
                Ref<MathNode> exp = Mathematica::MakeRef<MathNode>();
                arg->data = a;
                exp->data = fraction;
                arg->type = EMathNodeType::Number;
                exp->type = EMathNodeType::Number;

                operation->children.push_back(arg);
                operation->children.push_back(exp);
			}

            return result;
        }

        RationalNumber Raise(const RationalNumber& a, const Int32& b)
        {
            return RationalNumber();
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