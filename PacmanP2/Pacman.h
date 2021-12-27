#pragma once
#include "Creature.h"
#include "General.h"

// Handles the Pacman's specific movement and its lives.
class Pacman : public Creature
{
	static int lives;
public:

	Pacman(int x = 0, int y = 0, bool colour = false, char figure = Point::PACMAN, char dir = 's', char gameMode = Board::BEGINNER) : Creature(x, y, figure, colour, dir, gameMode) {};

	void init();

	void move(Board& b) override;

	int getlives() const
	{
		return lives;
	}

	void showLives(int x, int y, bool colour) const
	{
		gotoxy(x, y);
		if (colour)
			setColour(Board::WHITE);
		std::cout << "Lives: " << lives;
	}

	void initlives()
	{
		lives = 3;
	};

	void decreaseLife()
	{
		lives--;
	}
};