#include "mthpch.h"

#include "Core/Utility/Profiler.h"
#include "Core/Utility/Utils.h"

Profiler::Profiler() : mCurrentSession(nullptr), mProfileCount(0) {}

void Profiler::BeginProfile(const String& name, String outFilePath)
{
	StringStream filepath;

	if (!std::filesystem::is_directory("ProfilerLogs") || !std::filesystem::exists("ProfilerLogs"))
		std::filesystem::create_directories("ProfilerLogs");

	filepath << "ProfilerLogs/";

	if (outFilePath == "")
	{
		auto currentTime = std::time(nullptr);
		auto localTime = *std::localtime(&currentTime);

		filepath << "ProfilerSession_" << name << "_";
		filepath << std::put_time(&localTime, "%d-%m-%Y_%H-%M-%S");
	}
	else
	{
		filepath << outFilePath;
	}

	filepath << ".json";
	mOutputFile.open(filepath.str());

	WriteHeader();

	mCurrentSession = Mathematica::MakeScope<ProfilerSession>();
	mCurrentSession->name = name;
}

void Profiler::WriteProfile(const ProfileInformation& information)
{
	if (mProfileCount++ > 0) mOutputFile << ',';

	String name = information.name;
	Mathematica::Replace(name, '"', '\'');

	mOutputFile << "{";
	mOutputFile << "\"cat\": \"function\",";
	mOutputFile << "\"dur\":" << information.duration << ',';
	mOutputFile << "\"name\":\"" << name << "\",";
	mOutputFile << "\"ph\":\"X\",";
	mOutputFile << "\"pid\":" << information.processId << ',';
	mOutputFile << "\"tid\":" << information.threadId << ',';
	mOutputFile << "\"ts\":" << information.start;
	mOutputFile << "}";

	mOutputFile.flush();
}

void Profiler::EndProfile()
{
	WriteFooter();

	mOutputFile.close();
	mCurrentSession = nullptr;
	mProfileCount = 0;
}

Profiler& Profiler::Get()
{
	static Profiler* sInstance = new Profiler();
	return *sInstance;
}

void Profiler::WriteHeader()
{
	mOutputFile << "{\"otherData\": {},\"traceEvents\": [";
	mOutputFile.flush();
}

void Profiler::WriteFooter()
{
	mOutputFile << "]}";
	mOutputFile.flush();
}
