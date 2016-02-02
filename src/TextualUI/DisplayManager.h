#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER

#include <iostream>
#include <cctype>

#ifdef __linux__
#include <termios.h>
#elif __APPLE__
#include <termios.h>
#elif _WIN32
#include <conio.h>
#endif

class DisplayManager
{
#if defined(__linux__) || defined(__APPLE__)
    struct termios oldTerminal, newTerminal;
#endif
    
public:
    void PrepareDisplay();
    void ResetDisplay();
	void ClearScreen();
	char GetInput();
};

#endif //DISPLAY_MANAGER