#pragma once

#include "Utility/Utils.h"
#include "Core/Identifiable.h"

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
struct MNumber : public IIdentifiable
{
    int32 numerator;
    int32 denominator;
    ENumberType type;

    MNumber(int32 num = 0, int32 den = 1);

    MNumber operator+(MNumber other);
    MNumber operator-(MNumber other);
    MNumber operator*(MNumber other);
    MNumber operator/(MNumber other);

	void operator+=(MNumber other);
	void operator-=(MNumber other);
	void operator*=(MNumber other);
	void operator/=(MNumber other);

    double RawNumerical();
    MNumber LowestTerms();
};