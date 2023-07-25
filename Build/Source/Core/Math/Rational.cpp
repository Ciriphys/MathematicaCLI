#include "mthpch.h"

#include "Core/Math/Rational.h"

#include "Core/Number.h"

namespace Mathematica
{
	namespace Rational
	{
		Number Average(Vector<Number> numbers)
		{
			Number result;

			for (auto number : numbers)
			{
				result += number;
			}

			return result / numbers.size();
		}

		Number Average(Number first, Number second)
		{
			return (first + second) / 2;
		}

		Number Between(Number first, Number second)
		{
			return { first.numerator + second.numerator, first.denominator + second.denominator };
		}

		int32 Sign(float32 number)
		{
			MTH_ASSERT(number != 0, "DomainError: Zero is not in the domaain of Sign!");
			return number > 1 ? 1 : -1;
		}

		Number Farey(float32 number)
		{	
			Number lowerBound = { 0, 1 };
			Number upperBound = { 1, 1 };
			
			float32 delta = abs(number) - abs(Mathematica::Cast<int32>(number));
			Number between = Between(lowerBound, upperBound);
			float32 betweenValue = between.RawNumerical();

			if (!delta) return { Mathematica::Cast<int32>(number), 1 };

			while (abs(betweenValue - delta) > FLT_EPSILON)
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