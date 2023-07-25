#include "mthpch.h"

#include "Core/Identifiable.h"

#include "Utility/Conversions.h"
#include "Utility/Random.h"

Identifiable::Identifiable()
{
	mId = GenerateUUID();
}

String Identifiable::GenerateUUID()
{
	uint32 first     = RandomEngine::UnsignedInt(0, 0xffffffff);		
	uint32 second    = RandomEngine::UnsignedInt(0, 0xffff);			
	uint32 third	 = RandomEngine::UnsignedInt(0, 0xffff);			
	uint32 fourth	 = RandomEngine::UnsignedInt(0, 0xffff);
	uint32 fifth	 = RandomEngine::UnsignedInt(0, 0xffffffff);
	uint32 sixth	 = RandomEngine::UnsignedInt(0, 0xffff);

	StringStream UUID;
	UUID << Mathematica::Convert::Uint32ToHexString(first, 8) << "-";
	UUID << Mathematica::Convert::Uint32ToHexString(second, 4) << "-";
	UUID << Mathematica::Convert::Uint32ToHexString(third, 4) << "-";
	UUID << Mathematica::Convert::Uint32ToHexString(fourth, 4) << "-";
	UUID << Mathematica::Convert::Uint32ToHexString(fifth, 8) << Mathematica::Convert::Uint32ToHexString(sixth, 4);

	return UUID.str();
}

bool Identifiable::operator==(Identifiable other)
{
	return (mId == other.GetUUID());
}

bool Identifiable::operator!=(Identifiable other)
{
	return !(*this == other);
}