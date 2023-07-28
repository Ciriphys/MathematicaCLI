#pragma once

#include "Core/Utility/Types.h"
#include "Core/Utility/Timer.h"

#ifdef MTH_USE_PROFILER
#define MTH_PROFILE_SCOPE(name) Timer timer##__LINE__(name)
#define MTH_PROFILE_FUNCTION() MTH_PROFILE_SCOPE(__FUNCSIG__)
#define MTH_PROFILE_BEGIN(name, ...) Profiler::Get().BeginProfile(name, __VA_ARGS__);
#define MTH_PROFILE_END() Profiler::Get().EndProfile();
#else 
#define MTH_PROFILE_SCOPE(name)
#define MTH_PROFILE_FUNCTION()
#define MTH_PROFILE_BEGIN(name, ...)
#define MTH_PROFILE_END()
#endif 

struct ProfileInformation
{
	String name;
	int32 start;
	int32 end;
	int32 duration;

	int32 processId;
	int32 threadId;
};

struct ProfilerSession
{
	String name;
};

class Profiler
{
public: 
	Profiler();
	void BeginProfile(const String& name, String outFilePath = "");
	void WriteProfile(const ProfileInformation& information);
	void EndProfile();

	static Profiler& Get();

private: 
	void WriteHeader();
	void WriteFooter();

	Scope<ProfilerSession> mCurrentSession;
	OutFile mOutputFile;
	int32 mProfileCount;
};