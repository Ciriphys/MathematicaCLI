#pragma once

#include "Core/Identifiable.h"
#include "Core/Hashable.h"

#include "Core/Utility/Utils.h"

// NOTE : This definition might vary.
enum class ENumberType : Int32
{
    Integer,
    Rational,
};

enum class ESubset : Int32
{
	Integer,
	Rational,
	Irrational,
	Real,
};

struct RationalNumber
{
    Int32 numerator;
    Int32 denominator;
    ENumberType type;

    RationalNumber(Int32 num = 1, Int32 den = 1);
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

    Float32 RawNumerical();

    RationalNumber LowestTerms(Int32 num, Int32 den);
    void LowestTerms();
};

struct IrrationalNumber : public Hashable
{
	struct Data
	{
		String functionName;
		RationalNumber argument;

		Data(RationalNumber arg, String funcName = "") : argument(arg), functionName(funcName) {}
		// EFunctionType functionType; <--- It might be usefult to implement this in the future.
	};

	Data numerator;
	Data denominator;

	IrrationalNumber(Data num = {1}, Data den = {1});
	IrrationalNumber(const String& constantName);

	IrrationalNumber operator+(IrrationalNumber other);
	IrrationalNumber operator-(IrrationalNumber other);
	IrrationalNumber operator*(IrrationalNumber other);
	IrrationalNumber operator/(IrrationalNumber other);

	void operator+=(IrrationalNumber other);
	void operator-=(IrrationalNumber other);
	void operator*=(IrrationalNumber other);
	void operator/=(IrrationalNumber other);

	bool operator==(IrrationalNumber other);
	bool operator!=(IrrationalNumber other);
	bool operator>=(IrrationalNumber other);
	bool operator<=(IrrationalNumber other);
	bool operator> (IrrationalNumber other);
	bool operator< (IrrationalNumber other);

	virtual void Rehash() override;

	Float32 RawNumerical();
};

struct RealNumber
{
	RationalNumber rationalCoefficient;
	IrrationalNumber irrationalCoefficient;
	ESubset type;

	RealNumber(RationalNumber rational = {}, IrrationalNumber irrational = {});
	RealNumber(const String& strNumber);

	RealNumber operator+(RealNumber other);
	RealNumber operator-(RealNumber other);
	RealNumber operator*(RealNumber other);
	RealNumber operator/(RealNumber other);

	void operator+=(RealNumber other);
	void operator-=(RealNumber other);
	void operator*=(RealNumber other);
	void operator/=(RealNumber other);

	bool operator==(RealNumber other);
	bool operator!=(RealNumber other);
	bool operator>=(RealNumber other);
	bool operator<=(RealNumber other);
	bool operator> (RealNumber other);
	bool operator< (RealNumber other);

	Float32 RawNumerical();
};

// TODO : Move these functions somewhere else.
namespace Mathematica
{
    RationalNumber Absolute(RationalNumber number);
    Int32 Sign(RationalNumber number);
}