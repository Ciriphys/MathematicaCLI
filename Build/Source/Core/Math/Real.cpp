#include "mthpch.h"

#include "Core/Math/Real.h"

namespace Mathematica
{
	namespace Real
	{
		namespace Operation
		{
			MathExpression Add(const MathExpression& first, const MathExpression& second)
			{
				return {};
			}

			MathExpression Subtract(const MathExpression& first, const MathExpression& second)
			{
				return {};
			}

			MathExpression Multiply(const MathExpression& first, const MathExpression& second)
			{
				return {};
			}

			MathExpression Divide(const MathExpression& first, const MathExpression& second)
			{
				return MathExpression();
			}
		}

		Vector<RealNumber> ExecuteMultiply(const Vector<RealNumber>& first, const Vector<RealNumber>& second)
		{
			Vector<RealNumber> result = {};

			for (auto firstReal : first)
			{
				for (auto secondReal : second)
				{
					RealNumber multiplication;
					HashMap<IrrationalNumber, Int32, HashBinding<IrrationalNumber>, CompareHashable<IrrationalNumber>> symbolCounter;

					multiplication.rational = firstReal.rational * secondReal.rational;

					for (auto irrational : firstReal.irrational) symbolCounter[irrational] = symbolCounter.find(irrational) == symbolCounter.end() ? 0 : symbolCounter[irrational] + 1;
					for (auto irrational : secondReal.irrational) symbolCounter[irrational] = symbolCounter.find(irrational) == symbolCounter.end() ? 0 : symbolCounter[irrational] + 1;

					for (auto [irrational, count] : symbolCounter)
					{
						String functionName = Mathematica::Stringify(Mathematica::AnyCast<FRationalBinaryRational>(irrational.numerator->data));

						if (functionName == "Raise")
						{
							RationalNumber argument = Mathematica::AnyCast<RealNumber>(irrational.numerator->children[0]).rational;
							RationalNumber exponent = Mathematica::AnyCast<RealNumber>(irrational.numerator->children[1]).rational;

							RationalNumber newExponent = exponent * count;

							Int32 lastExponent = Mathematica::Cast<Int32>(newExponent.RawNumerical());
							newExponent.numerator -= lastExponent;

							// Exponentiate using Integer and multiply the result with multiplication.rational.

							if (newExponent.numerator != 0)
							{
								// We have another irrational part, so append it to multiplication.
								
							}
						}
					}

					if (multiplication.irrational.Size() == 0) multiplication.irrational.EmplaceBack();
					result.push_back(multiplication);
				}
			}

			return ExecuteSimplify(result);
		}

		Vector<RealNumber> ExecuteSimplify(const Vector<RealNumber>& expression)
		{
			Vector<RealNumber> result = {};
			Vector<bool> used(expression.size(), true);

			for (UInt64 i = 0; i < expression.size(); i++)
			{
				RealNumber iReal = expression[i];

				for (UInt64 j = i + 1; j < expression.size() && used[i]; j++)
				{
					RealNumber jReal = expression[j];

					if (Hashable::Compare(iReal.irrational, jReal.irrational) && used[j])
					{
						iReal.rational += jReal.rational;
						used[j] = false;
					}
				}

				used[i] = false;
				result.push_back(iReal);
			}

			return result;
		}
	}
}
