#include "General.h"
#include "Point.h"

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

char randDirection()
{
	int dir;

	dir = rand() % 4;

	if (dir == 0)
		return Point::LEFT;

	else if (dir == 1)
		return Point::RIGHT;

	else if (dir == 2)
		return Point::UP;

	else
		return Point::DOWN;
}

void setColour(int colour)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}