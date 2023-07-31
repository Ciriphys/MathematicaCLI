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

Int32 RandomEngine::Int(Int32 minRange, Int32 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_int_distribution<Int32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

UInt32 RandomEngine::UnsignedInt(UInt32 minRange, UInt32 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_int_distribution<UInt32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

Float32 RandomEngine::Float(Float32 minRange, Float32 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_real_distribution<Float32> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

Float64 RandomEngine::Double(Float64 minRange, Float64 maxRange)
{
	MTH_ASSERT(sInstance, "RandomEngine instance has not been initialized. Please invoke RandomEngine::Init().");

	std::uniform_real_distribution<Float64> uniformDistribution(minRange, maxRange);
	return uniformDistribution(mMersenneTwister);
}

RandomEngine::RandomEngine()
{
	sInstance = this;
	mMersenneTwister = MersenneTwister(mRandomDevice());
}
