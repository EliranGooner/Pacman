#pragma once
#include "General.h"

// Includes board structure and responsible for breadcrumbs count.
class Board
{
	static int breadLeft;
	static int bread;
	static int extraPoints;
	char b[26][81] = {};
	int max_X;
	int max_Y;
	int livesX = 0;
	int livesY = 0;

public:
	enum { WHITE = 7, RED = 12, BLUE = 9, YELLOW = 14 };
	enum { WALL = 0, CRUMBS = 2, CLEAR = 3 };
	enum { BEGINNER = '1', INTERMEDIATE = '2', ADVANCED = '3' };

	Board() {};

	int getLivesX() const
	{
		return livesX;
	}

	int getLivesY() const
	{
		return livesY;
	}

	void UpdatelivesY(int num)
	{
		livesY = num;
	}

	void UpdateLivesX(int num)
	{
		livesX = num;
	}

	void initBread()
	{
		breadLeft = 0;
		bread = 0;
		extraPoints = 0;
	};

	void printBoard(bool colour) const;

	void getRsize(std::ifstream& file);

	int getBreadLeft() const
	{
		return breadLeft;
	}

	int getBread() const
	{
		return bread;
	}

	int getmaxY() const
	{
		return max_Y;
	}

	int getmaxX() const
	{
		return max_X;
	}

	void removeBread()
	{
		breadLeft--;
	}

	void UpdateBread()
	{
		breadLeft++;
	}

	void UpdateMaxY(int num)
	{
		max_Y = num;
	}

	void upDateCell(int x, int y, char ch)
	{
		b[x][y] = ch;
	};

	void upDatefuitP(int x)
	{
		extraPoints += x;
	};

	char checkBoardCell(int x, int y) const;

	void eatBread(int x, int y)
	{
		b[x][y] = ' ';
		bread++;
	};

	void showPoints(bool colour) const
	{
		gotoxy(livesX, livesY + 1);
		if (colour)
			setColour(WHITE);
		std::cout << "Points:" << bread + extraPoints;
	};
};