#pragma once

class RandomEngine
{
public:
	static void Init();

	static Int32 Int(Int32 minRange = 0, Int32 maxRange = 0x7fffffff);
	static UInt32 UnsignedInt(UInt32 minRange = 0, UInt32 maxRange = 0xffffffff);
	static Float32 Float(Float32 minRange = 0.0, Float32 maxRange = 1.0);
	static Float64 Double(Float64 minRange = 0.0, Float64 maxRange = 1.0);

	~RandomEngine() = default;

private:
	
	RandomEngine();

	static RandomDevice mRandomDevice;
	static MersenneTwister mMersenneTwister;
	static RandomEngine* sInstance;
};