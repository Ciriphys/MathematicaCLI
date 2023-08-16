#include "mthpch.h"

#include "Core/Utility/Profiler.h"
#include "Core/Hashable.h"

Hashable::Hashable()
{
	ResetHash();
}

bool Hashable::Compare(const Hashable& first, const Hashable& second)
{
	return first.mHash == second.mHash;
}

// NOTE : I generated this Hash function randomly, in the future this might change.
void Hashable::Hash(UInt32 seed)
{
	MTH_PROFILE_FUNCTION();

	UInt32 offset = 0x2f39f82f + seed;

	const UInt16 magicHigh = 0xaf13;
	const UInt16 magicLow = 0x4b71;

	UInt16 seedHigh = MTH_HIGH_DWORD(offset) * magicLow;
	UInt16 seedLow = MTH_LOW_DWORD(offset) * magicHigh;

	seedHigh ^= (seedLow >> 7) | (seedHigh << 23);
	seedLow |= (seedHigh << 13) * (seedLow << 3);

	mHash *= ((Mathematica::Cast<UInt32>(seedLow) << 16) | seedHigh);
	return;
}
