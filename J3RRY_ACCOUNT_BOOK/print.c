#include "print.h"
#include <Windows.h>
#include <stdio.h>
void printRed(const char* str) {
#ifdef _WIN32
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO defaultScreenInfo;
	GetConsoleScreenBufferInfo(out, &defaultScreenInfo);
	SetConsoleTextAttribute(out,
		FOREGROUND_RED | FOREGROUND_INTENSITY
	);
	printf("%s", str);
	SetConsoleTextAttribute(out, defaultScreenInfo.wAttributes);
#else
	printf("\033[1m%s\033[0m", str);

#endif
}