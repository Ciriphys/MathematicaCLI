#pragma once

struct RationalNumber;

namespace Mathematica 
{
    namespace Operation
    {
        RationalNumber Add      (const RationalNumber& a, const RationalNumber& b);
        RationalNumber Subtract (const RationalNumber& a, const RationalNumber& b);
        RationalNumber Multiply (const RationalNumber& a, const RationalNumber& b);
        RationalNumber Divide   (const RationalNumber& a, const RationalNumber& b);

        RationalNumber Mod      (const RationalNumber& a, const RationalNumber& b);
    }
}