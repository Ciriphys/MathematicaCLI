#include "mthpch.h"

#include "Core/Math/Integer.h"
#include "Core/Math/Operations.h"

#include "Core/Number.h"

MNumber::MNumber(int32 num, int32 den) : numerator(num), denominator(den), type(ENumberType::Real) 
{
    *this = LowestTerms();
    
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

MNumber::MNumber(const MString& strNumber)
{
    // TODO : Add support for fractions and real numbers.
    numerator = std::atoi(strNumber.c_str());
    denominator = 1;

    type = ENumberType::Integer;
}

double MNumber::RawNumerical()
{
    return (double)numerator / (double)denominator;
}

MNumber MNumber::LowestTerms()
{
    int32 gcd = Mathematica::Integer::GreatestCommonDivisor(numerator, denominator);
    return { numerator / gcd, denominator / gcd };
}

MNumber MNumber::operator+(MNumber other)
{
    return Mathematica::Operation::Add(*this, other);
}

MNumber MNumber::operator-(MNumber other)
{
    return Mathematica::Operation::Subtract(*this, other);
}

MNumber MNumber::operator*(MNumber other)
{
    return Mathematica::Operation::Multiply(*this, other);
}

MNumber MNumber::operator/(MNumber other)
{
    return Mathematica::Operation::Divide(*this, other);
}

void MNumber::operator+=(MNumber other)
{
    *this = Mathematica::Operation::Add(*this, other);
}

void MNumber::operator-=(MNumber other)
{
    *this = Mathematica::Operation::Subtract(*this, other);
}

void MNumber::operator*=(MNumber other)
{
    *this = Mathematica::Operation::Multiply(*this, other);
}

void MNumber::operator/=(MNumber other)
{
    *this = Mathematica::Operation::Divide(*this, other);
}
