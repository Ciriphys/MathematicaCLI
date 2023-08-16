#pragma once

#include "Core/Math/Number.h"

namespace Mathematica
{	
	namespace Real
	{
		namespace Operation
		{
			MathExpression Add(const MathExpression& first, const MathExpression& second);
			MathExpression Subtract(const MathExpression& first, const MathExpression& second);
			MathExpression Multiply(const MathExpression& first, const MathExpression& second);
			MathExpression Divide(const MathExpression& first, const MathExpression& second);
		}

		Vector<RealNumber> ExecuteSimplify(const Vector<RealNumber>& expression);
		Vector<RealNumber> ExecuteMultiply(const Vector<RealNumber>& first, const Vector<RealNumber>& second);
	}

	namespace Irrational
	{
		RealNumber ProcessIrrationalSubTree(const Ref<MathNode>& subTree, const UInt32& counter);
	}
}