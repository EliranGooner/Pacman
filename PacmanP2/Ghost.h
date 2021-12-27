#pragma once
#include "General.h"
#include "Creature.h"


// Handles the Ghost's specific movement.
class Ghost : public Creature
{
public:
	Ghost(int x = 0, int y = 0, bool colour = false, char figure = Point::GHOST, char dir = 'd', char gameMode = Board::BEGINNER) : Creature(x, y, figure, colour, dir, gameMode) {};
	void init(char dir = 'd');
	void move(Board& b) override;
};