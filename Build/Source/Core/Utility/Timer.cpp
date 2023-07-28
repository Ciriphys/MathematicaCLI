#include "mthpch.h"

#include "Core/Utility/Profiler.h"
#include "Core/Utility/Timer.h"

Timer::Timer(const String& name) : mName(name), mRunning(false)
{
	Start();
}

Timer::~Timer()
{
	if (mRunning) Stop();
}

void Timer::Start()
{
	mStartTimepoint = HRClock::now();
	mRunning = true;
}

void Timer::Stop()
{
	TimePoint<SteadyClock> endTimepoint = HRClock::now();

	int32 start = std::chrono::time_point_cast<Microseconds>(mStartTimepoint).time_since_epoch().count();
	int32 end = std::chrono::time_point_cast<Microseconds>(endTimepoint).time_since_epoch().count();
	int32 duration = end - start;

	// TODO : Add process and thread id.
	Profiler::Get().WriteProfile({ mName, start, end, duration, 0, 0 });

	mRunning = false;
}
