#include "mthpch.h"

#ifdef MTH_WIN
	#include <conio.h>
#endif

#include "App.h"
#include "Utility/Utils.h"

MApp* MApp::sInstance = nullptr;

MApp* MApp::Get() 
{
    if (!sInstance) new MApp();
    return sInstance;
}

void MApp::Execute()
{
	for(auto [command, params] : mCommands)
	{
		if (command == "--solve" || command == "-s")
		{
			Mathematica::AppCommand::Solve();
		}
		else if (command == "--help" || command == "-h")
		{
			Mathematica::AppCommand::Help();
		}
		else if (command == "--about" || command == "--info" || command == "-?")
		{
			Mathematica::AppCommand::About();
		}
		else if (command == "--exit" || command == "--abort" || command == "--quick")
		{
			bRunning = false;
		}
		else
		{
			Mathematica::AppCommand::Unknown(command);
		}
	}
}

void MApp::TypeMode()
{
	MString userInput;
	std::getline(std::cin, userInput);
	mArguments = Mathematica::SeparateString(userInput);
    GenerateCommandMap();
}

void MApp::GenerateCommandMap()
{
	MString currentCommand = "None";
	for (auto argument : mArguments)
	{
		if (argument.rfind("-", 0) == 0 || argument.rfind("--", 0) == 0)
		{
			currentCommand = argument;
			Mathematica::TransformToLower(currentCommand);
			mCommands[currentCommand] = MVector<MString>();
		}
		else
		{
			mCommands[currentCommand].push_back(argument);
		}

		std::cout << argument << " ";
	}
}

void MApp::DrawMenu()
{
	Mathematica::ClearScreen();
	std::cout << "==== Mathematica CLI: Menu ====" << std::endl;
	std::cout << "Requested task: ";

	if (mArguments.empty())
	{
		std::cout << "None.";
		bTypeMode = true;
	}
	else
	{
		GenerateCommandMap();
		bTypeMode = false;
	}

	std::cout << std::endl << std::endl;

	if (bTypeMode)
	{
		std::cout << "> ";
		TypeMode();
		bTypeMode = false;
	}
	else
	{
		Execute();
		mArguments.clear();
		mCommands.clear();
		bTypeMode = true;
	}
}

void MApp::Alert(MString alert)
{
	Mathematica::AppCommand::DisplayAlert(alert);
}

MApp::MApp()
{
    sInstance = this;

	mLexer = MLexer();
}

void MApp::LoadArguments(int argc, char** argv)
{
    for(int i = 1; i < argc; i++)
    {
        mArguments.push_back(argv[i]);
    }
}

void MApp::ExtractArguments(MString arguments)
{
	// TODO : Use Utils implementation, which is currently located in MLexer class.

    MString currentArgument = "";
    for (auto c : arguments)
    {
        if (c == ' ')
        {
            mArguments.push_back(currentArgument);
            currentArgument = "";
        }
        else
        {
            currentArgument += c;
        }
    }
}

void MApp::Run() 
{
    do 
    {
        DrawMenu();
    } 
    while (bRunning);

    Abort();
}

int MApp::Abort()
{
	Mathematica::AppCommand::DisplayExitMessage();
    return 0;
}


// === Commands ===

void Mathematica::AppCommand::Help()
{
	Mathematica::ClearScreen();
	std::cout << "==== List of commands: ====" << std::endl;
	std::cout << " * --solve -s <equation> \t: Solves the input equation." << std::endl;
	std::cout << " * --help -h <params?> \t\t: Shows a list of commands or information about a command." << std::endl;
	std::cout << " * --about --info -? \t\t: Shows the about tab." << std::endl;
	std::cout << " * --exit --abort \t\t: Terminates the process." << std::endl;

	WaitKey();

	return;
}

void Mathematica::AppCommand::Solve()
{
	Mathematica::ClearScreen();
	std::cout << "==== MathematicaCLI: Solve ====" << std::endl;

	auto app = MApp::Get();
	auto commands = app->GetCommands();
	auto lexer = app->GetLexer();

	MString commandKey = commands.find("--solve") == commands.end() ? "-s" : "--solve";
	for (auto equation : commands[commandKey])
	{
		MVector<MLexiconToken> tokens = lexer.GenerateTokens(equation); 
		MTH_DEBUG_INFO(Mathematica::DisplayTokenArray(tokens));
	}

	WaitKey();

	return;
}

void Mathematica::AppCommand::About()
{
	Mathematica::ClearScreen();
	std::cout << "==== About MathematicaCLI: ====" << std::endl;
	std::cout << " * Written by Ciridev with <3" << std::endl;
	std::cout << " * " << MTH_VERSION << std::endl;
	std::cout << " * Distributed under the MIT License." << std::endl;
	std::cout << " * To learn more, visit https://github.com/ZeXo-Softwares/MathematicaCLI." << std::endl;

	WaitKey();

	return;
}

void Mathematica::AppCommand::DisplayAlert(MString alert)
{
	Mathematica::ClearScreen();
	std::cout << "==== Mathematica CLI Alert: ====" << std::endl;
	std::cout << alert << std::endl;

	WaitKey();
	return;
}

void Mathematica::AppCommand::DisplayExitMessage()
{
	Mathematica::ClearScreen();
	std::cout << "==== MathematicaCLI: ====" << std::endl;
	std::cout << "Mathematica ~ " << MTH_VERSION << std::endl;
}

void Mathematica::AppCommand::Unknown(MString command)
{
	Mathematica::ClearScreen();
	std::cout << "==== Unknown command: ====" << std::endl;
	std::cout << "An unknown command has been passed (" << command <<"). Check for mistakes!" << std::endl;

	WaitKey();

	return;
}

void Mathematica::AppCommand::WaitKey()
{
	#ifndef MTH_WIN
		system("stty raw");
	#endif
	std::cout << std::endl << std::endl;
	std::cout << "Press any key to close.";
	#ifndef MTH_WIN
		getchar();
		system("stty cooked");
	#endif
	#ifdef MTH_WIN
		(void)getch();
	#endif
}