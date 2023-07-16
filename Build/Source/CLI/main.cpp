#include "mthpch.h"

#include "App.h"

int main(int argc, char** argv)
{
	MApp* app = MApp::Get();
	app->LoadArguments(argc, argv);
	app->Run();
	int result = app->Abort();

	delete app;

	return result;
}