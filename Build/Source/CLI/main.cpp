#include "mthpch.h"

#include "CLI/Application.h"

Int32 main(Int32 argc, char** argv)
{
	Application* app = Application::Get();
	app->LoadArguments(argc, argv);
	app->Run();
	Int32 result = app->Abort();

	delete app;

	return result;
}