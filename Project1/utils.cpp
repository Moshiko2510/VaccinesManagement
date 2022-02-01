#include "utils.h"
#include "symbolics.h"
#include <windows.h>
//#include "Battleship.h" 

/* Program utils functions */

void clrscr()
{
	// upper left corner
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

//==========================================================================================
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//==========================================================================================
void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

//==========================================================================================
void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK) {
		SetConsoleTextAttribute(hCon, color);
	}
	else {
		SetConsoleTextAttribute(hCon, color | background_color * 16 + color);
	}
}

//==========================================================================================
int mark2color(char c)
{
	if (c == 'H') return GREEN;
	if (c == 'M') return RED;
	if (c == 'S') return BLACK;
	if (c == '.') return BLUE;
}
