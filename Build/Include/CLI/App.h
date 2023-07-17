#pragma once

#include "Core/Lexer.h"

#include "Utility/Types.h"

class MApp 
{ 
    public:
        static MApp* Get();
        void LoadArguments(int32 argc, char** argv);
        void Run();
        int32 Abort();

        ~MApp() = default;

        void Alert(MString alert);

        MLexer GetLexer() const { return mLexer; }
        MHashMap<MString, MVector<MString>> GetCommands() const { return mCommands; }

    private:
        MApp();

        void Execute();
        void TypeMode();
        void GenerateCommandMap();
        void DrawMenu();

        bool bRunning = true;
        bool bTypeMode = true;

        MVector<MString> mArguments;
        MHashMap<MString, MVector<MString>> mCommands;

        MLexer mLexer;

        static MApp* sInstance;
};

namespace Mathematica
{
    namespace AppCommand
    {
        void Help();
        void Solve();
        void About();

        void DisplayAlert(MString alert);
        void DisplayExitMessage();

        void Unknown(MString command);

        void WaitKey();
    }
}