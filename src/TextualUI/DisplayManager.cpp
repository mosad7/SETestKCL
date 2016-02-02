
#include "DisplayManager.h"

void DisplayManager::PrepareDisplay()
{
#if defined(__linux__) || defined(__APPLE__)
	//store the current terminal settings
    tcgetattr(0, &oldTerminal);
    newTerminal = oldTerminal;
	//disabled input bufferring (i.e. no need for Enter key)
    newTerminal.c_lflag &= ~ICANON;
    newTerminal.c_lflag &= ECHO;
	//apply the new settings
    tcsetattr(0, TCSANOW, &newTerminal);
#endif
}

void DisplayManager::ResetDisplay()
{
#if defined(__linux__) || defined(__APPLE__)
    tcsetattr(0, TCSANOW, &oldTerminal);
#endif
}

void DisplayManager::ClearScreen()
{
#ifdef __linux__
	std::system("clear");
#elif __APPLE__
    std::system("clear");
#elif _WIN32
	std::system("cls");
#endif
}

char DisplayManager::GetInput()
{
	char ch;

#ifdef __linux__
	ch = getchar();
#elif __APPLE__
    ch = getchar();
#elif _WIN32
	ch = _getche();
#endif

	return tolower(ch);
}