
#include "DisplayManager.h"
#include "Negotiator.h"

int main(int argc, char *argv[])
{
	bool simulateExecTime = false;

	//parse argument list
	if (argc > 1)
	{
		//"-s" is used to simulate a dummy execution time for processing Y or N
		std::string arg = argv[1];
		if (arg.compare("-s") == 0)
		{
			simulateExecTime = true;
		}
	}

	//initialize the textual display manager
	DisplayManager displayUtils;
	displayUtils.PrepareDisplay();

	//initialize the negotiator controller
	Negotiator negotiate;
	negotiate.Start(simulateExecTime);

    char ch;
	while ((ch = displayUtils.GetInput()) != 'q')
	{
		//update the Negotiator object
		negotiate.AppendInput(ch);

		//update the textual user interface
		displayUtils.ClearScreen();

		switch (ch)
		{
		case 'y':
			std::cout << "YES" << std::endl;
			break;
		case 'n':
			std::cout << "NO" << std::endl;
			break;
		case 'z':
			std::cout << "Last input removed" << std::endl;
			break;
		case 's':
			std::cout << "Waiting for summary to be processed ..." << std::endl;
			displayUtils.ClearScreen();
			std::cout << negotiate.GenerateSummary() << std::endl;
			break;
		case 'h':
			std::cout << negotiate.GenerateHelpText();
			std::cout << "Press any key to continue" << std::endl;
			displayUtils.GetInput();
			displayUtils.ClearScreen();
			break;
		default:
			continue;
			break;
		}
	}

	//update the textual user interface
	displayUtils.ClearScreen();

	//instruct the negotiator to complete processing the input buffer
	//then to generate a summary of the results
	negotiate.Stop();
	displayUtils.ClearScreen();
	std::cout << negotiate.GenerateSummary() << std::endl;
	
	//wait for the user input
	std::cout << std::endl << "Press Enter key to exit" << std::endl;
	std::cin.ignore();
    
	//restore previous display settings
    displayUtils.ResetDisplay();

	return 0;
}

