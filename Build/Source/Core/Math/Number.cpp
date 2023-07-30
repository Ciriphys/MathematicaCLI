#include "mthpch.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Rational.h"
#include "Core/Math/Integer.h"
#include "Core/Math/Number.h"

#include "Core/Utility/Conversions.h"
#include "Core/Utility/Profiler.h"

RationalNumber::RationalNumber(int32 num, int32 den) : numerator(num), denominator(den), type(ENumberType::Real)
{
    MTH_ASSERT(denominator != 0, "NumberInitError: Cannot divide by zero!");

    LowestTerms();

    // TODO : This implementation does not include Real type numbers. For now the only allowed types are Integer and Rational.
    if (denominator == 1)
    {
        type = ENumberType::Integer;
    }
    else
    {
        type = ENumberType::Rational;
    }
}

RationalNumber::RationalNumber(const String& strNumber)
{
    // TODO : Add support for fractions and real numbers.
    float32 rawNumerical = Mathematica::Convert::StringToFloat32(strNumber);

    if (rawNumerical != Mathematica::Cast<int32>(rawNumerical))
    {
        RationalNumber fraction = Mathematica::Rational::Farey(rawNumerical);
		numerator = fraction.numerator;
		denominator = fraction.denominator;
        type = ENumberType::Rational;
    }
    else
    {
        numerator = Mathematica::Cast<int32>(rawNumerical);
        denominator = 1;
        type = ENumberType::Integer;
    }
}

float32 RationalNumber::RawNumerical()
{
    return (float32)numerator / (float32)denominator;
}

RationalNumber RationalNumber::LowestTerms(int32 numerator, int32 denominator)
{
    int32 gcd = Mathematica::Integer::GreatestCommonDivisor(numerator, denominator);
    return { numerator / gcd, denominator / gcd};
}

void RationalNumber::LowestTerms()
{
    int32 gcd = Mathematica::Integer::GreatestCommonDivisor(numerator, denominator);
    
    numerator /= gcd;
    denominator /= gcd;
}

RationalNumber RationalNumber::operator+(RationalNumber other)
{
    return Mathematica::Operation::Add(*this, other);
}

RationalNumber RationalNumber::operator-(RationalNumber other)
{
    return Mathematica::Operation::Subtract(*this, other);
}

RationalNumber RationalNumber::operator*(RationalNumber other)
{
    return Mathematica::Operation::Multiply(*this, other);
}

RationalNumber RationalNumber::operator/(RationalNumber other)
{
    return Mathematica::Operation::Divide(*this, other);
}

void RationalNumber::operator+=(RationalNumber other)
{
    *this = Mathematica::Operation::Add(*this, other);
}

void RationalNumber::operator-=(RationalNumber other)
{
    *this = Mathematica::Operation::Subtract(*this, other);
}

void RationalNumber::operator*=(RationalNumber other)
{
    *this = Mathematica::Operation::Multiply(*this, other);
}

void RationalNumber::operator/=(RationalNumber other)
{
    *this = Mathematica::Operation::Divide(*this, other);
}

bool RationalNumber::operator==(RationalNumber other)
{
    return numerator * other.denominator == denominator * other.numerator;
}

bool RationalNumber::operator!=(RationalNumber other)
{
    return !(*this == other);
}

bool RationalNumber::operator>=(RationalNumber other)
{
    return numerator * other.denominator >= denominator * other.numerator;
}

bool RationalNumber::operator<=(RationalNumber other)
{
    return numerator * other.denominator <= denominator * other.numerator;
}

bool RationalNumber::operator>(RationalNumber other)
{
    return numerator * other.denominator > denominator * other.numerator;
}

bool RationalNumber::operator<(RationalNumber other)
{
    return numerator * other.denominator < denominator * other.numerator;
}

namespace Mathematica
{
    RationalNumber Absolute(RationalNumber number)
    {
        MTH_PROFILE_FUNCTION();

        return RationalNumber(number.numerator > 0 ? number.numerator : -number.numerator, number.denominator > 0 ? number.denominator : -number.denominator);
    }

    int32 Sign(RationalNumber number)
    {
        MTH_PROFILE_FUNCTION();

        MTH_ASSERT(number != 0, "DomainError: Zero is not in the domain of Sign!");
        return number > 0 ? 1 : -1;
    }
}