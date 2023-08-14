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
		Int32 Sign(Float32 number);

		RationalNumber Farey(Float32 number);

		// Rationality
		bool IsRootRational(RationalNumber arg, Int32 index);
	}
}