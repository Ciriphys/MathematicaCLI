#pragma once

#include "Core/Solver.h"
#include "Core/Parser.h"
#include "Core/Lexer.h"

#include "Utility/Types.h"

class MApplication 
{ 
    public:
        static MApplication* Get();
        void LoadArguments(int32 argc, char** argv);
        void Run();
        int32 Abort();

        ~MApplication() = default;

        void Alert(MString alert);

        void RefreshAPI();

        MRef<MLexer> GetLexer() const { return mLexer; }
        MRef<MParser> GetParser() const { return mParser; }
        MRef<MSolver> GetSolveEngine() const { return mSolveEngine; }

        MHashMap<MString, MVector<MString>> GetCommands() const { return mCommands; }

    private:
        MApplication();

        void Execute();
        void TypeMode();
        void GenerateCommandMap();
        void DrawMenu();

        bool bRunning = true;
        bool bTypeMode = true;

        MVector<MString> mArguments;
        MHashMap<MString, MVector<MString>> mCommands;

        MRef<MLexer> mLexer;
        MRef<MParser> mParser;
        MRef<MSolver> mSolveEngine;

        static MApplication* sInstance;
};

namespace Mathematica
{
    namespace AppCommand
    {
        void Help();
        void Solve();
        void About();

        void DisplayAlert(MString alert, MString title = "Mathematica CLI Alert:");
        void DisplayExitMessage();

        void Unknown(MString command);

        void WaitKey();
    }
}