#pragma once

#include "Core/MathNode.h"

#include "Core/Utility/Utils.h"
#include "Core/Utility/Types.h"

class Hashable
{
public:
	Hashable(); 
	UInt32 GetHash() const { return mHash; }

	virtual void Rehash() = 0;

	static bool Compare(const Hashable& first, const Hashable& second);

protected:
	template<typename T>
	void HashField(T field);

private:
	void Hash(UInt32 seed);

	UInt32 mHash;
};

template<typename T>
inline void Hashable::HashField(T field)
{
	MTH_ASSERT(false, "HashError: To use Hashable with this type, you have to implement your own hash function!");
}

template<>
inline void Hashable::HashField(UInt32 field)
{
	Hash(field);
}

template<>
inline void Hashable::HashField(String field)
{
	UInt32 hashNumber = 0;

	const UInt16 magicHigh = 0xaf13;
	const UInt16 magicLow = 0x4b71;

	for (auto c : field) hashNumber += c * magicHigh - magicLow / c;

	Hash(hashNumber);
}

template<>
inline void Hashable::HashField(Ref<MathNode> field)
{
	Hash(*MTH_UINT_ADDRESS_OF(field));

	for (Ref<MathNode> child : field->children) HashField(child);
}
