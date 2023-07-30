#include "mthpch.h"

#include "Core/Math/Rational.h"
#include "Core/Math/Number.h"

#include "Core/Utility/Profiler.h"

namespace Mathematica
{
	namespace Rational
	{
		RationalNumber Average(Vector<RationalNumber> numbers)
		{
			MTH_PROFILE_FUNCTION();

			RationalNumber result;

			for (auto number : numbers)
			{
				result += number;
			}

			return result / Mathematica::Cast<int32>(numbers.size());
		}

		RationalNumber Average(RationalNumber first, RationalNumber second)
		{
			MTH_PROFILE_FUNCTION();

			return (first + second) / 2;
		}

		RationalNumber Between(RationalNumber first, RationalNumber second)
		{
			MTH_PROFILE_FUNCTION();

			return { first.numerator + second.numerator, first.denominator + second.denominator };
		}

		int32 Sign(float32 number)
		{
			MTH_PROFILE_FUNCTION();

			MTH_ASSERT(number != 0, "DomainError: Zero is not in the domain of Sign!");
			return number > 0 ? 1 : -1;
		}

		RationalNumber Farey(float32 number)
		{	
			MTH_PROFILE_FUNCTION();

			RationalNumber lowerBound = { 0, 1 };
			RationalNumber upperBound = { 1, 1 };
			
			float32 delta = abs(number) - abs(Mathematica::Cast<int32>(number));
			RationalNumber between = Between(lowerBound, upperBound);
			float32 betweenValue = between.RawNumerical();

			if (!delta) return { Mathematica::Cast<int32>(number), 1 };

			while (abs(betweenValue - delta) > MTH_FLOAT32_EPSILON)
			{
				if (delta < betweenValue)
				{
					upperBound = between;
				}
				else
				{
					lowerBound = between;
				}

				between = Between(lowerBound, upperBound);
				betweenValue = between.RawNumerical();
			}

			between.numerator *= Mathematica::Rational::Sign(number);
			return abs(number) < 1 ? between : between + Mathematica::Cast<int32>(number);
		}
	}
}