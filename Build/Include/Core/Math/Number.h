#pragma once

#include "Core/Identifiable.h"

#include "Core/Utility/Utils.h"

// NOTE : This definition might vary.
enum class ENumberType : int32
{
    Integer,
    Rational,
    Real,
    Complex,

    AngleDegrees,
    AngleRadians
};

// TODO : Add support for real numbers. Currently this definition is valid for rationals.
struct RationalNumber
{
    int32 numerator;
    int32 denominator;
    ENumberType type;

    RationalNumber(int32 num = 0, int32 den = 1);
    RationalNumber(const String& strNumber);

    RationalNumber operator+(RationalNumber other);
    RationalNumber operator-(RationalNumber other);
    RationalNumber operator*(RationalNumber other);
    RationalNumber operator/(RationalNumber other);

	void operator+=(RationalNumber other);
	void operator-=(RationalNumber other);
	void operator*=(RationalNumber other);
	void operator/=(RationalNumber other);

    bool operator==(RationalNumber other);
    bool operator!=(RationalNumber other);
    bool operator>=(RationalNumber other);
    bool operator<=(RationalNumber other);
    bool operator> (RationalNumber other);
    bool operator< (RationalNumber other);

    float32 RawNumerical();

    RationalNumber LowestTerms(int32 num, int32 den);
    void LowestTerms();
};

// TODO : Move these functions somewhere else.
namespace Mathematica
{
    RationalNumber Absolute(RationalNumber number);
    int32 Sign(RationalNumber number);
}