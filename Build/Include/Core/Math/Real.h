#pragma once

#include "Core/Math/Number.h"

namespace Mathematica
{	
	namespace Real
	{
		MathExpression Add(const MathExpression& a, const MathExpression& b);
		MathExpression Subtract(const MathExpression& a, const MathExpression& b);
		MathExpression Multiply(const MathExpression& a, const MathExpression& b);
		MathExpression Divide(const MathExpression& a, const MathExpression& b);
	}
}