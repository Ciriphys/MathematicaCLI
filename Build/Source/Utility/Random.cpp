#include "mthpch.h"

#include "Utility/Utils.h"
#include "Utility/Random.h"

MRandom* MRandom::sInstance = nullptr;
MRandomDevice MRandom::mRandomDevice;
MMersenneTwister MRandom::mMersenneTwister;

void MRandom::Init()
{
	if (!sInstance) new MRandom();
	return;
}

int32 MRandom::Int(int32 minRange, int32 maxRange)
{
	MTH_ASSERT(sInstance, "MRandom instance has not been initialized. Please call MRandom::Init().");

	std::uniform_int_distribution<int32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

uint32 MRandom::UnsignedInt(uint32 minRange, uint32 maxRange)
{
	MTH_ASSERT(sInstance, "MRandom instance has not been initialized. Please call MRandom::Init().");

	std::uniform_int_distribution<uint32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

double MRandom::Double(double minRange, double maxRange)
{
	MTH_ASSERT(sInstance, "MRandom instance has not been initialized. Please call MRandom::Init().");

	std::uniform_real_distribution<double> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

MRandom::MRandom()
{
	sInstance = this;
	mMersenneTwister = MMersenneTwister(mRandomDevice());
}
