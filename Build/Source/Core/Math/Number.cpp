#include "mthpch.h"

#include "Core/Math/Operations.h"
#include "Core/Math/Rational.h"
#include "Core/Math/Integer.h"
#include "Core/Math/Number.h"

#include "Core/Utility/Conversions.h"

Number::Number(int32 num, int32 den) : numerator(num), denominator(den), type(ENumberType::Real)
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

Number::Number(const String& strNumber)
{
    // TODO : Add support for fractions and real numbers.
    float32 rawNumerical = Mathematica::Convert::StringToFloat32(strNumber);
    Number fraction = Mathematica::Rational::Farey(rawNumerical);

    numerator = fraction.numerator;
    denominator = fraction.denominator;

    type = ENumberType::Integer;
}

float32 Number::RawNumerical()
{
    return (float32)numerator / (float32)denominator;
}

Number Number::LowestTerms(int32 numerator, int32 denominator)
{
    int32 gcd = Mathematica::Integer::GreatestCommonDivisor(numerator, denominator);
    return { numerator / gcd, denominator / gcd};
}

void Number::LowestTerms()
{
    int32 gcd = Mathematica::Integer::GreatestCommonDivisor(numerator, denominator);
    
    numerator /= gcd;
    denominator /= gcd;
}

Number Number::operator+(Number other)
{
    return Mathematica::Operation::Add(*this, other);
}

Number Number::operator-(Number other)
{
    return Mathematica::Operation::Subtract(*this, other);
}

Number Number::operator*(Number other)
{
    return Mathematica::Operation::Multiply(*this, other);
}

Number Number::operator/(Number other)
{
    return Mathematica::Operation::Divide(*this, other);
}

void Number::operator+=(Number other)
{
    *this = Mathematica::Operation::Add(*this, other);
}

void Number::operator-=(Number other)
{
    *this = Mathematica::Operation::Subtract(*this, other);
}

void Number::operator*=(Number other)
{
    *this = Mathematica::Operation::Multiply(*this, other);
}

void Number::operator/=(Number other)
{
    *this = Mathematica::Operation::Divide(*this, other);
}

bool Number::operator==(Number other)
{
    return numerator * other.denominator == denominator * other.numerator;
}

bool Number::operator!=(Number other)
{
    return !(*this == other);
}

bool Number::operator>=(Number other)
{
    return numerator * other.denominator >= denominator * other.numerator;
}

bool Number::operator<=(Number other)
{
    return numerator * other.denominator <= denominator * other.numerator;
}

bool Number::operator>(Number other)
{
    return numerator * other.denominator > denominator * other.numerator;
}

bool Number::operator<(Number other)
{
    return numerator * other.denominator < denominator * other.numerator;
}

namespace Mathematica
{
    Number Absolute(Number number)
    {
        return Number(number.numerator > 0 ? number.numerator : -number.numerator, number.denominator > 0 ? number.denominator : -number.denominator);
    }

    int32 Sign(Number number)
    {
        MTH_ASSERT(number != 0, "DomainError: Zero is not in the domain of Sign!");
        return number > 0 ? 1 : -1;
    }
}