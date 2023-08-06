#include "mthpch.h"

#include "Core/Math/Real.h"

namespace Mathematica
{
	namespace Real
	{
		MathExpression Add(const MathExpression& a, const MathExpression& b)
		{
			MathExpression result = a;
			MathExpression appended = {};

			for (UInt64 j = 0; j < b.size; j++)
			{
				bool bShouldAppend = true;
				const RealNumber& bReal = b[j];

				for (UInt64 i = 0; i < a.size; i++)
				{
					RealNumber& aReal = result[i];

					if (Hashable::Compare(aReal.irrationalCoefficients, bReal.irrationalCoefficients))
					{
						aReal.rationalCoefficient += bReal.rationalCoefficient;
						bShouldAppend = false;
						break;
					}
				}

				if (bShouldAppend) appended.expression.push_back(bReal);
			}

			for (auto appendReal : appended) result.expression.push_back(appendReal);
			return result;
		}

		MathExpression Subtract(const MathExpression& a, const MathExpression& b)
		{
			MathExpression result = a;
			MathExpression appended = {};

			for (UInt64 j = 0; j < b.size; j++)
			{
				bool bShouldAppend = true;
				const RealNumber& bReal = b[j];

				for (UInt64 i = 0; i < a.size; i++)
				{
					RealNumber& aReal = result[i];

					if (Hashable::Compare(aReal.irrationalCoefficients, bReal.irrationalCoefficients))
					{
						aReal.rationalCoefficient -= bReal.rationalCoefficient;
						bShouldAppend = false;
						break;
					}
				}

				if (bShouldAppend) appended.expression.push_back(bReal);
			}

			for (auto appendReal : appended) result.expression.push_back(appendReal);
			return result;
		}

		MathExpression Multiply(const MathExpression& a, const MathExpression& b)
		{
			MathExpression result = {};

			for (UInt64 j = 0; j < b.size; j++)
			{
				const RealNumber& bReal = b[j];

				for (UInt64 i = 0; i < a.size; i++)
				{
					const RealNumber& aReal = a[i];
					RealNumber multiplication;

					multiplication.rationalCoefficient = aReal.rationalCoefficient * bReal.rationalCoefficient;

					for (auto irrational : aReal.irrationalCoefficients) multiplication.irrationalCoefficients.push_back(irrational);
					for (auto irrational : bReal.irrationalCoefficients) multiplication.irrationalCoefficients.push_back(irrational);

					result.expression.push_back(multiplication);
				}
			}

			return MathExpression();
		}

		MathExpression Divide(const MathExpression& a, const MathExpression& b)
		{
			return MathExpression();
		}
	}
}