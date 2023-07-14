#pragma once

#include "Types.h"

class App 
{ 
    public:
        static App* Get();
        void LoadCL(int argc, char** argv);
        void Run();

        int Abort();

        ~App() = default;

    private:
        App();
        MVector<MString> mArguments;
        static App* sInstance;
};