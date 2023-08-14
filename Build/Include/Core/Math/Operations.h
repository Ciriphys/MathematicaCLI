#pragma once

#include "Core/Utility/Types.h"

namespace Mathematica 
{
    namespace Operation
    {
		RationalNumber Add          (const RationalNumber& a, const RationalNumber& b);
		RationalNumber Subtract     (const RationalNumber& a, const RationalNumber& b);
		RationalNumber Multiply     (const RationalNumber& a, const RationalNumber& b);
		RationalNumber Divide       (const RationalNumber& a, const RationalNumber& b);
        RealNumber     Exponentiate (const RationalNumber& a, const RationalNumber& b);

        RationalNumber Raise        (const RationalNumber& a, const Int32& b);

        RationalNumber Mod          (const RationalNumber& a, const RationalNumber& b);
    }
}