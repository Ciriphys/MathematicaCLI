#include "mthpch.h"

#include "Core/Utility/Utils.h"
#include "Core/Utility/Random.h"

RandomEngine* RandomEngine::sInstance = nullptr;
RandomDevice RandomEngine::mRandomDevice;
MersenneTwister RandomEngine::mMersenneTwister;

void RandomEngine::Init()
{
	if (!sInstance) new RandomEngine();
	return;
}

int32 RandomEngine::Int(int32 minRange, int32 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_int_distribution<int32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

uint32 RandomEngine::UnsignedInt(uint32 minRange, uint32 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_int_distribution<uint32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

float32 RandomEngine::Float(float32 minRange, float32 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_real_distribution<float32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

float64 RandomEngine::Double(float64 minRange, float64 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_real_distribution<float64> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

RandomEngine::RandomEngine()
{
	sInstance = this;
	mMersenneTwister = MersenneTwister(mRandomDevice());
}
