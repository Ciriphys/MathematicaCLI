#include "mthpch.h"

#include "CLI/App.h"

int32 main(int32 argc, char** argv)
{
	MApp* app = MApp::Get();
	app->LoadArguments(argc, argv);
	app->Run();
	int32 result = app->Abort();

	delete app;

	return result;
}