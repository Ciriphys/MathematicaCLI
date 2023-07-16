#pragma once

#include "Core/Lexer.h"

#include "Utility/Types.h"

class MApp 
{ 
    public:
        static MApp* Get();
        void LoadArguments(int argc, char** argv);
        void Run();
        int Abort();

        ~MApp() = default;

        void Alert(MString alert);

    private:
        MApp();

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

			static void DisplayAlert(MString alert);
			static void DisplayExitMessage();

			static void Unknown(MString command);

		private:
			static void WaitKey();
		};

        bool bRunning = true;
        bool bTypeMode = true;

        MVector<MString> mArguments;
        MHashMap<MString, MVector<MString>> mCommands;

        MLexer mLexer;

        static MApp* sInstance;
};