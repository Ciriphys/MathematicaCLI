#include "mthpch.h"

#include "Core/Identifiable.h"

#include "Utility/Conversions.h"
#include "Utility/Random.h"

IIdentifiable::IIdentifiable()
{
	mId = GenerateUUID();
}

MString IIdentifiable::GenerateUUID()
{
	uint32 first     = MRandom::UnsignedInt(0, 0xffffffff);		
	uint32 second    = MRandom::UnsignedInt(0, 0xffff);			
	uint32 third	 = MRandom::UnsignedInt(0, 0xffff);			
	uint32 fourth	 = MRandom::UnsignedInt(0, 0xffff);
	uint32 fifth	 = MRandom::UnsignedInt(0, 0xffffffff);
	uint32 sixth	 = MRandom::UnsignedInt(0, 0xffff);

	MStringStream UUID;
	UUID << Mathematica::Convert::IntToHexString(first, 8) << "-";
	UUID << Mathematica::Convert::IntToHexString(second, 4) << "-";
	UUID << Mathematica::Convert::IntToHexString(third, 4) << "-";
	UUID << Mathematica::Convert::IntToHexString(fourth, 4) << "-";
	UUID << Mathematica::Convert::IntToHexString(fifth, 8) << Mathematica::Convert::IntToHexString(sixth, 4);

	return UUID.str();
}

bool IIdentifiable::operator==(IIdentifiable other)
{
	return (mId == other.GetUUID());
}

bool IIdentifiable::operator!=(IIdentifiable other)
{
	return !(*this == other);
}