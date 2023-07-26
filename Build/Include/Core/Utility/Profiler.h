#pragma once

#include "Core/Utility/Types.h"
#include "Core/Utility/Timer.h"

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