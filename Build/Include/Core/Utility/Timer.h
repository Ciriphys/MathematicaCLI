#pragma once

#include "Core/Utility/Types.h"

class Timer
{
public:
	Timer(const String& name);
	~Timer();

	void Start();
	void Stop();

private:
	String mName;
	TimePoint<SteadyClock> mStartTimepoint;
	bool mRunning;
};
