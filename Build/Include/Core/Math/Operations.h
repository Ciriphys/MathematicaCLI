#pragma once

struct Number;

namespace Mathematica 
{
    namespace Operation
    {
        Number Add      (const Number& a, const Number& b);
        Number Subtract (const Number& a, const Number& b);
        Number Multiply (const Number& a, const Number& b);
        Number Divide   (const Number& a, const Number& b);

        Number Mod      (const Number& a, const Number& b);
    }
}