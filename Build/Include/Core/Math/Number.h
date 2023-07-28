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
struct Number
{
    int32 numerator;
    int32 denominator;
    ENumberType type;

    Number(int32 num = 0, int32 den = 1);
    Number(const String& strNumber);

    Number operator+(Number other);
    Number operator-(Number other);
    Number operator*(Number other);
    Number operator/(Number other);

	void operator+=(Number other);
	void operator-=(Number other);
	void operator*=(Number other);
	void operator/=(Number other);

    bool operator==(Number other);
    bool operator!=(Number other);
    bool operator>=(Number other);
    bool operator<=(Number other);
    bool operator> (Number other);
    bool operator< (Number other);

    float32 RawNumerical();

    Number LowestTerms(int32 num, int32 den);
    void LowestTerms();
};

// TODO : Move these functions somewhere else.
namespace Mathematica
{
    Number Absolute(Number number);
    int32 Sign(Number number);
}