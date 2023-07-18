#include "mthpch.h"

#include "Core/Identifiable.h"
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

	// TODO : Fix length of UUID.

	MStringStream UUID;
	UUID << std::hex << first   << "-";
	UUID << std::hex << second  << "-";
	UUID << std::hex << third   << "-";
	UUID << std::hex << fourth  << "-";
	UUID << std::hex << fifth << sixth;

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