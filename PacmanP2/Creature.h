#pragma once
#include "Point.h"

class Creature {
	Point p;
protected:
	bool colour;
	int startX = 0;
	int startY = 0;
public:

	Creature(int _startX, int _startY, char _figure, bool _colour, char _dir, char _gameMode);

	Creature(Board& b, bool _colour = false);

	virtual ~Creature() {};

	Point& getPoint()
	{
		return p;
	}

	virtual void move(Board& b) = 0;
};