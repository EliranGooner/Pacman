#pragma once
#include "Creature.h"
#include "General.h"

class Fruit : public Creature
{
public:
	Fruit(int x = 0, int y = 0, bool colour = false, char figure = '5', char dir = 'd', char gameMode = Board::BEGINNER) :Creature(x, y, figure, colour, dir, gameMode) {};

	Fruit(Board& b, bool _colour = false) : Creature(b, _colour) {};

	Fruit(Fruit const&) = delete;

	Fruit& operator=(Fruit const&) = delete;

	void move(Board& b) override;

	virtual ~Fruit() {};
};