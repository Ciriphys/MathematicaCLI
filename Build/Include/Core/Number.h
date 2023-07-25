#pragma once

#include "Core/Identifiable.h"

#include "Utility/Utils.h"

// This definition might vary.
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
struct Number : public Identifiable
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

    double RawNumerical();
    Number LowestTerms();
};