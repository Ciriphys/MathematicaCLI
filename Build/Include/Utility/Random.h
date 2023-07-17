#pragma once

class MRandom
{
public:
	static void Init();

	static int32 Int(int32 minRange = 0, int32 maxRange = 0x7fffffff);
	static uint32 UnsignedInt(uint32 minRange = 0, uint32 maxRange = 0xffffffff);
	static double Double(double minRange = 0.0, double maxRange = 1.0);

	~MRandom() = default;

private:
	
	MRandom();

	static MRandomDevice mRandomDevice;
	static MMersenneTwister mMersenneTwister;
	static MRandom* sInstance;
};