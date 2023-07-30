#pragma once

#include "Core/Solver.h"
#include "Core/Parser.h"
#include "Core/Lexer.h"

#include "Core/Utility/Types.h"

class Application 
{ 
    public:
        static Application* Get();
        void LoadArguments(int32 argc, char** argv);
        void Run();
        int32 Abort();

        ~Application() = default;

        void Alert(String alert);

        void RefreshAPI();

        Ref<Lexer> GetLexer() const { return mLexer; }
        Ref<Parser> GetParser() const { return mParser; }
        Ref<Solver> GetSolveEngine() const { return mSolveEngine; }

        HashMap<String, Vector<String>> GetCommands() const { return mCommands; }

    private:
        Application();

        void Execute();
        void TypeMode();
        void GenerateCommandMap();
        void DrawMenu();

        bool bRunning = true;
        bool bTypeMode = true;

        Vector<String> mArguments;
        HashMap<String, Vector<String>> mCommands;

        Ref<Lexer> mLexer;
        Ref<Parser> mParser;
        Ref<Solver> mSolveEngine;

        static Application* sInstance;
};

namespace Mathematica
{
    namespace AppCommand
    {
        void Help();
        void Solve();
        void About();
        void Test();

        void DisplayAlert(String alert, String title = "Mathematica CLI Alert:");
        void DisplayExitMessage();

        void Unknown(String command);

        void WaitKey();
    }
}