#pragma once

#include "Core/Identifiable.h"
#include "Core/Hashable.h"
#include "Core/MathNode.h"

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
	Ref<MathNode> numerator;
	Ref<MathNode> denominator;

	IrrationalNumber(Ref<MathNode> num = Mathematica::MakeRef<MathNode>(), Ref<MathNode> den = Mathematica::MakeRef<MathNode>());
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

struct IrrationalPart : private Vector<IrrationalNumber>, public Hashable
{
	IrrationalPart() {}
	IrrationalPart(size_t count, const IrrationalNumber& val) : Vector<IrrationalNumber>(count, val) { Rehash(); }

	template<typename ...Args>
	inline decltype(auto) EmplaceBack(Args&&... args)
	{
		emplace_back(std::forward<Args>(args)...);
		Rehash();
	}

	void PushBack(const IrrationalNumber& what);
	void PushBack(IrrationalNumber&& what);

	void PopBack();
	UInt64 Size() const { return size(); }

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
	Vector<RealNumber> numerator;
	Vector<RealNumber> denominator;

	MathExpression(Vector<RealNumber> num = {}, Vector<RealNumber> den = { {} }) {}
	MathExpression(RealNumber real);
};

// TODO : Move these functions somewhere else.
namespace Mathematica
{
    RationalNumber Absolute(RationalNumber number);
    Int32 Sign(RationalNumber number);
}

template<>
inline void Hashable::HashField(RationalNumber field)
{
	Hash(field.numerator);
	Hash(field.denominator);
}

template<>
inline void Hashable::HashField(IrrationalNumber field)
{
	HashField(field.numerator);
	HashField(field.denominator);
}
