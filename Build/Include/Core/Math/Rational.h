#pragma once

#include "Utility/Types.h"

namespace Mathematica
{
	namespace Rational
	{
		Number Average(Vector<Number> numbers);
		Number Average(Number first, Number second);

		Number Between(Number first, Number second);

		// TODO : Move this function somewhere else.
		int32 Sign(float32 number);

		Number Farey(float32 number);
	}
}