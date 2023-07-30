#pragma once

#include "Core/Utility/Types.h"

namespace Mathematica
{
	namespace Rational
	{
		RationalNumber Average(Vector<RationalNumber> numbers);
		RationalNumber Average(RationalNumber first, RationalNumber second);

		RationalNumber Between(RationalNumber first, RationalNumber second);

		// TODO : Move this function somewhere else.
		int32 Sign(float32 number);

		RationalNumber Farey(float32 number);
	}
}