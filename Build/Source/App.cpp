#include "mthpch.h"

#include <conio.h>

#include "App.h"
#include "Utils.h"

App* App::sInstance = nullptr;

App* App::Get() 
{
    if (!sInstance) new App();
    return sInstance;
}

void App::Execute()
{
	for(auto [command, params] : mCommands)
	{
		if (command == "--solve" || command == "-s")
		{
			Command::Solve();
		}
		else if (command == "--help" || command == "-h")
		{
			Command::Help();
		}
		else if (command == "--about" || command == "--info" || command == "-?")
		{
			Command::About();
		}
		else if (command == "--exit" || command == "--abort")
		{
			bRunning = false;
		}
		else
		{
			Command::Unknown(command);
		}
	}
}

void App::TypeMode()
{
	MString userInput;
	std::getline(std::cin, userInput);
	ExtractArguments(userInput + " ");
    GenerateCommandMap();
}

void App::GenerateCommandMap()
{
	MString currentCommand = "None";
	for (auto argument : mArguments)
	{
		if (argument.rfind("-", 0) == 0 || argument.rfind("--", 0) == 0)
		{
			currentCommand = argument;
			std::transform(currentCommand.begin(), currentCommand.end(), currentCommand.begin(), std::tolower);
			mCommands[currentCommand] = MVector<MString>();
		}
		else
		{
			mCommands[currentCommand].push_back(argument);
		}

		std::cout << argument << " ";
	}
}

void App::DrawMenu()
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

App::App()
{
    sInstance = this;
}

void App::LoadArguments(int argc, char** argv)
{
    for(int i = 1; i < argc; i++)
    {
        mArguments.push_back(argv[i]);
    }
}

void App::ExtractArguments(MString arguments)
{
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

void App::Run() 
{
    do 
    {
        DrawMenu();
    } 
    while (bRunning);

    Abort();
}

int App::Abort()
{
	Command::DisplayExitMessage();
    return 0;
}


// === Commands ===

void App::Command::Help()
{
	Mathematica::ClearScreen();
	std::cout << "==== List of commands: ====" << std::endl;
	std::cout << " * --solve -s <equation> \t: Solves the input equation." << std::endl;
	std::cout << " * --help -h <params?> \t\t: Shows a list of commands or information about a command." << std::endl;
	std::cout << " * --about --info -? \t\t: Shows the about tab." << std::endl;
	std::cout << " * --exit --abort \t\t: Terminates the process." << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << "Press any key to close.";
	(void)getch();

	return;
}

void App::Command::Solve()
{
	Mathematica::ClearScreen();
	std::cout << "This functionality is not available yet!" << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << "Press any key to close.";
	(void)getch();

	return;
}

void App::Command::About()
{
	Mathematica::ClearScreen();
	std::cout << "==== About MathematicaCLI: ====" << std::endl;
	std::cout << " * Written by Ciridev with <3" << std::endl;
	std::cout << " * " << MTH_VERSION << std::endl;
	std::cout << " * Distributed under the MIT License." << std::endl;
	std::cout << " * To learn more, visit https://github.com/ZeXo-Softwares/MathematicaCLI." << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << "Press any key to close.";
	(void)getch();

	return;
}

void App::Command::DisplayExitMessage()
{
	Mathematica::ClearScreen();
	std::cout << "==== MathematicaCLI: ====" << std::endl;
	std::cout << "Mathematica ~ " << MTH_VERSION << std::endl;
}

void App::Command::Unknown(MString command)
{
	Mathematica::ClearScreen();
	std::cout << "==== Unknown command: ====" << std::endl;
	std::cout << "An unknown command has been passed (" << command <<"). Check for mistakes!" << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << "Press any key to close.";
	(void)getch();

	return;
}
