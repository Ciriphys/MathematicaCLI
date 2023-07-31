#include "mthpch.h"

#include "Core/Identifiable.h"

#include "Core/Utility/Conversions.h"
#include "Core/Utility/Random.h"

Identifiable::Identifiable()
{
	mId = GenerateUUID();
}

String Identifiable::GenerateUUID()
{
	UInt32 first     = RandomEngine::UnsignedInt(0, 0xffffffff);		
	UInt32 second    = RandomEngine::UnsignedInt(0, 0xffff);			
	UInt32 third	 = RandomEngine::UnsignedInt(0, 0xffff);			
	UInt32 fourth	 = RandomEngine::UnsignedInt(0, 0xffff);
	UInt32 fifth	 = RandomEngine::UnsignedInt(0, 0xffffffff);
	UInt32 sixth	 = RandomEngine::UnsignedInt(0, 0xffff);

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