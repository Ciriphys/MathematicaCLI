#pragma once

class RandomEngine
{
public:
	static void Init();

	static int32 Int(int32 minRange = 0, int32 maxRange = 0x7fffffff);
	static uint32 UnsignedInt(uint32 minRange = 0, uint32 maxRange = 0xffffffff);
	static float64 Double(float64 minRange = 0.0, float64 maxRange = 1.0);

	~RandomEngine() = default;

private:
	
	RandomEngine();

	static RandomDevice mRandomDevice;
	static MersenneTwister mMersenneTwister;
	static RandomEngine* sInstance;
};