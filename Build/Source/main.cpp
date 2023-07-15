#include "mthpch.h"

#include "App.h"

#if defined(MTH_WIN) || defined(MTH_MACOS)

int main(int argc, char** argv)
{
	App* app = App::Get();
	app->LoadArguments(argc, argv);
	app->Run();
	int result = app->Abort();

	delete app;

	return result;
}

#else 
	#error MathematicaCLI is not available on your platform.
#endif