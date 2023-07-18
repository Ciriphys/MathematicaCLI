#pragma once

struct MNumber;

namespace Mathematica 
{
    namespace Operation
    {
        MNumber Add      (const MNumber& a, const MNumber& b);
        MNumber Subtract (const MNumber& a, const MNumber& b);
        MNumber Multiply (const MNumber& a, const MNumber& b);
        MNumber Divide   (const MNumber& a, const MNumber& b);

        MNumber Mod      (const MNumber& a, const MNumber& b);
    }
}