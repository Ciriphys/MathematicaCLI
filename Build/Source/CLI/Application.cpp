#include "mthpch.h"

#include "CLI/Application.h"

#include "Core/Utility/Profiler.h"
#include "Core/Utility/Random.h"
#include "Core/Utility/Utils.h"

#include "Core/Math/Integer.h"
#include "Core/Math/Number.h"
#include "Core/Math/Real.h"

Application* Application::sInstance = nullptr;

Application* Application::Get() 
{
    if (!sInstance) new Application();
    return sInstance;
}

void Application::Execute()
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
		else if (command == "--test")
		{
			Mathematica::AppCommand::Test();
		}
		else
		{
			Mathematica::AppCommand::Unknown(command);
		}
	}
}

void Application::TypeMode()
{
	String userInput;
	std::getline(std::cin, userInput);
	mArguments = Mathematica::SeparateString(userInput);
    GenerateCommandMap();
}

void Application::GenerateCommandMap()
{
	String currentCommand = "None";
	for (auto argument : mArguments)
	{
		if (argument.rfind("-", 0) == 0 || argument.rfind("--", 0) == 0)
		{
			currentCommand = argument;
			Mathematica::TransformToLower(currentCommand);
			mCommands[currentCommand] = Vector<String>();
		}
		else
		{
			mCommands[currentCommand].push_back(argument);
		}

		std::cout << argument << " ";
	}
}

void Application::DrawMenu()
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
		std::cout << "$ ";
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

void Application::Alert(String alert)
{
	Mathematica::AppCommand::DisplayAlert(alert);
}

void Application::RefreshAPI()
{
	mLexer = Mathematica::MakeRef<Lexer>();
	mParser = Mathematica::MakeRef<Parser>();
	mSolveEngine = Mathematica::MakeRef<Solver>();
}

Application::Application()
{
	MTH_PROFILE_BEGIN("Benchmark");

    sInstance = this;
	RefreshAPI();

	RandomEngine::Init();
}

void Application::LoadArguments(Int32 argc, char** argv)
{
    for(Int32 i = 1; i < argc; i++)
    {
        mArguments.push_back(argv[i]);
    }
}

void Application::Run() 
{
    do 
    {
        DrawMenu();
    } 
    while (bRunning);

    Abort();
}

Int32 Application::Abort()
{
	MTH_PROFILE_END();

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

// REFACTOR : Refactor this function!
void Mathematica::AppCommand::Solve()
{
	Mathematica::ClearScreen();
	std::cout << "==== MathematicaCLI: Solve ====" << std::endl;

	auto app = Application::Get();
	auto commands = app->GetCommands();

	String commandKey = commands.find("--solve") == commands.end() ? "-s" : "--solve";
	for (auto equation : commands[commandKey])
	{
		auto lexer = app->GetLexer();
		auto parser = app->GetParser();
		auto solveEngine = app->GetSolveEngine();

		lexer->GenerateTokens(equation); 
		Vector<LexiconToken> tokens = lexer->GetTokens();

		parser->InitParser(tokens, lexer->GetOperationIndex(), lexer->GetScopeCounter());
		auto root = parser->GenerateTree();

		// TODO : Parse user input to choose which task should be performed.
		solveEngine->InitSolver(root, parser->GetExecutionFlow());
		auto result = solveEngine->SolveTree();

		StringStream alertText;

		alertText << "Steps:\n";

		for (auto step : ExplanationSystem::Get().GetSolution())
		{
			alertText << step << "\n";
		}

		alertText << "Done.\n\n";

		alertText << "Result: " << Stringify(result) << "\n\n" << "Additional info:\n";
		alertText.precision(6);
		alertText << std::fixed << "Decimal value: " << result.RawNumerical() << "\n";

		if (result.type == ENumberType::Integer && result != 0)
		{
			bool primality = Mathematica::Integer::IsPrime(Mathematica::Absolute(result)) || result == 1;

			if (!primality)
			{
				alertText << "Factorization: ";
				auto factors = Mathematica::Integer::Factorize(Mathematica::Absolute(result));
				if (Mathematica::Sign(result) == -1)
				{
					alertText << "-1 * ";
				}

				for (auto [factor, exponent] : factors)
				{
					alertText << factor;
					if (exponent != 1) alertText << "^" << exponent;
					alertText << ((--factors.end())->first != factor ? " * " : "\n");
				}
			}
			
			if(Mathematica::Sign(result) == 1) alertText << "Is prime? " << (primality && result != 1 ? "Yes\n" : "No\n");
		}

		Mathematica::AppCommand::DisplayAlert(alertText.str(), "Result of equation: " + equation);
		app->RefreshAPI();
		ExplanationSystem::Get().Flush();
	}

	return;
}

void Mathematica::AppCommand::About()
{
	Mathematica::ClearScreen();
	std::cout << "==== About MathematicaCLI: ====" << std::endl;
	std::cout << " * Written by Ciridev with <3" << std::endl;
	std::cout << " * " << MTH_VERSION << std::endl;
    std::cout << " * System: " << MTH_PLATFORM << std::endl;
	std::cout << " * Distributed under the MIT License." << std::endl;
	std::cout << " * To learn more, visit https://github.com/Ciridev/MathematicaCLI." << std::endl;

	WaitKey();
	return;
}

void Mathematica::AppCommand::Test()
{
	Mathematica::ClearScreen();

	Ref<MathNode> add = Mathematica::MakeRef<MathNode>();
	Ref<MathNode> left = Mathematica::MakeRef<MathNode>();
	Ref<MathNode> right = Mathematica::MakeRef<MathNode>();

	left->data = RationalNumber(2);
	right->data = RationalNumber(3);

	add->data = &Mathematica::Absolute;
	add->children.push_back(left);
	add->children.push_back(right);

	Ref<MathNode> add2 = Mathematica::MakeRef<MathNode>();
	Ref<MathNode> left2 = Mathematica::MakeRef<MathNode>();
	Ref<MathNode> right2 = Mathematica::MakeRef<MathNode>();

	left2->data = RationalNumber(2);
	right2->data = RationalNumber(3);

	add2->data = &Mathematica::IsLetter;
	add2->children.push_back(left2);
	add2->children.push_back(right2);

	IrrationalPart ip, ip2;
	ip.EmplaceBack(add);
	ip2.EmplaceBack(add2);
	 
	std::cout << ip.GetHash() << std::endl;
	std::cout << ip2.GetHash() << std::endl;

	WaitKey();
	return;
}

void Mathematica::AppCommand::DisplayAlert(String alert, String title)
{
	Mathematica::ClearScreen();
	std::cout << "==== " << title << " ====" << std::endl;
	std::cout << alert;

	WaitKey();
	return;
}

void Mathematica::AppCommand::DisplayExitMessage()
{
	Mathematica::ClearScreen();
	std::cout << "==== MathematicaCLI: ====" << std::endl;
	std::cout << "Mathematica ~ " << MTH_VERSION << std::endl;
}

void Mathematica::AppCommand::Unknown(String command)
{
	Mathematica::ClearScreen();
	std::cout << "==== Unknown command: ====" << std::endl;
	std::cout << "An unknown command has been passed (" << command <<"). Check for mistakes!" << std::endl;

	WaitKey();
	return;
}

void Mathematica::AppCommand::WaitKey()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(0.5s);

    #ifdef MTH_WIN
        std::cout << std::endl << "Press any key to continue" << std::endl;
        MTH_UNUSED(_getch());
    #else
        std::cout << std::endl << "Press enter to continue" << std::endl;
        MTH_UNUSED(std::cin.get());
    #endif
    
    return;
}
