#pragma once

#include "Types.h"

class App 
{ 
    public:
        static App* Get();
        void LoadArguments(int argc, char** argv);
        void Run();
        int Abort();

        ~App() = default;

    private:
        App();

        void Execute();
        void TypeMode();
        void ExtractArguments(MString arguments);
        void GenerateCommandMap();
        void DrawMenu();

        // Static functions may be changing in the future.
        struct Command
        {
            static void Help();
            static void Solve();
            static void About();

            static void DisplayExitMessage();

            static void Unknown(MString command);

            private:
            static void WaitKey();
        };

        bool bRunning = true;
        bool bTypeMode = true;

        MVector<MString> mArguments;
        MHashMap<MString, MVector<MString>> mCommands;
        static App* sInstance;
};