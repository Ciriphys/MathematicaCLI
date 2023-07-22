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
struct MNumber : public IIdentifiable
{
    int32 numerator;
    int32 denominator;
    ENumberType type;

    MNumber(int32 num = 0, int32 den = 1);
    MNumber(const MString& strNumber);

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