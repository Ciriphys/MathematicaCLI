#include "mthpch.h"

#include "Core/Number.h"
#include "Core/Math/Integer.h"

MNumber::MNumber(int32 num, int32 den) : numerator(num), denominator(den) {}

MNumber MNumber::LowestTerms()
{
    int32 gcd = Mathematica::Integers::GreatestCommonDivisor(numerator, denominator);
    return { numerator / gcd, denominator / gcd };
}