#pragma once
#include "Board.h"
#include "General.h"

// Includes functions for drawing, erasing, moving (and more) of the game characters. 
class Point
{
	char figure;
	char dir;
	int x = 0;
	int y = 0;
	bool colour;
	char gameLevel;

public:
	enum { PACMAN = '@', GHOST = '$' };
	enum { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's' };

	Point(int _x = 0, int _y = 0, char _figure = ' ', bool _colour = false, char _dir = STAY, char _gameLevel = Board::BEGINNER) : x(_x), y(_y), figure(_figure), colour(_colour), dir(_dir), gameLevel(_gameLevel) {};

	Point(Board& b, bool _colour = false) : colour(_colour)
	{
		randFigure(b);
		randPoint(b);
		dir = randDirection();
	};

	void randPoint(Board& b);

	void randFigure(Board& b);

	void draw(char figure1) const;

	int minDistance(char grid[25][80]);

	void erase() const
	{
		gotoxy(x, y);
		std::cout << ' ' << std::endl;
	}

	void changeDir(char ch)
	{
		dir = ch;
	}

	int getX() const
	{
		return x;
	}

	int getY() const
	{
		return y;
	}

	int getFig() const
	{
		return figure;
	}

	void updateX(int x1)
	{
		x = x1;
	}

	void updateY(int y1)
	{
		y = y1;
	}

	// Uses a BFS algorithm to find the shortest path to the pacman.
	void chaseMode(const Point& pacPoint, const Board& b);

	bool nextPoint(Board& b);

	bool ifFruit() const
	{
		if (figure == '5' || figure == '6' || figure == '7' || figure == '8' || figure == '9')
			return true;
		return false;
	}
};