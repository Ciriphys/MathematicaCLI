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
	mStartTimepoint = SteadyClock::now();
	mRunning = true;
}

void Timer::Stop()
{
	TimePoint<SteadyClock> endTimepoint = SteadyClock::now();

	Int32 start = std::chrono::time_point_cast<Microseconds>(mStartTimepoint).time_since_epoch().count();
	Int32 end = std::chrono::time_point_cast<Microseconds>(endTimepoint).time_since_epoch().count();
	Int32 duration = end - start;

	// TODO : Add process and thread id.
	// TODO : Open the WriteProfile on a different thread to allow faster performance.
	Profiler::Get().WriteProfile({ mName, start, end, duration, 0, 0 });

	mRunning = false;
}
