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

	const RationalNumber& operator+(RationalNumber other) const;
	const RationalNumber& operator-(RationalNumber other) const;
	const RationalNumber& operator*(RationalNumber other) const;
	const RationalNumber& operator/(RationalNumber other) const;

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

struct IrrationalPart : public Vector<IrrationalNumber>, public Hashable
{
	IrrationalPart() {}
	IrrationalPart(size_t count, const IrrationalNumber& val) : Vector<IrrationalNumber>(count, val) {}

	virtual void Rehash() override;
};

struct RealNumber
{
	RationalNumber rationalCoefficient;
	IrrationalPart irrationalCoefficients;
	ESubset type;

	// TODO : Change to irrational part.
	RealNumber(RationalNumber rational = {}, IrrationalPart irrational = {});
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

struct MathExpression
{
	Vector<RealNumber> expression;

	MathExpression(Vector<RealNumber> expression = {});
	MathExpression(RealNumber real);

	Vector<RealNumber>::iterator begin() { return expression.begin(); }
	Vector<RealNumber>::iterator end() { return expression.end(); }

	Vector<RealNumber>::const_iterator begin() const { return expression.begin(); }
	Vector<RealNumber>::const_iterator end() const { return expression.end(); }

	UInt64 size;

	RealNumber& operator[] (UInt64 position);
	const RealNumber& operator[] (UInt64 position) const;

	// NOTE : Adding an initializer list constructor might be useful.
};

// TODO : Move these functions somewhere else.
namespace Mathematica
{
    RationalNumber Absolute(RationalNumber number);
    Int32 Sign(RationalNumber number);
}

template<>
inline void Hashable::HashField(IrrationalNumber field)
{
	field.Rehash();
}