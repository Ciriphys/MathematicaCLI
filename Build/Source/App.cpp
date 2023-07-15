#include "mthpch.h"

#include "App.h"
#include "Utils.h"

App* App::sInstance = nullptr;

App* App::Get() 
{
    if (!sInstance) new App();
    return sInstance;
}

App::App() 
{
    sInstance = this;
}

void App::LoadCL(int argc, char** argv)
{
    for(int i = 1; i < argc; i++)
    {
        this->mArguments.push_back(argv[i]);
    }
}
void App::Run() 
{
    for (auto arg : mArguments)
    {
        std::cout << arg << std::endl;
    }
}

int App::Abort()
{
    return 0;
}