#pragma once
#include "General.h"
#include "Point.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"

// Handles the gameplay - includes functions for winning, losing, pausing etc.
class Game
{
	Pacman pac;
	Ghost ghosts[4];
	Fruit* fru;
	Board b;
	char gameLevel;
	bool colour;
	int numOfGhosts = 0;
	bool pause = false;
public:

	Game(bool _colour, char _gameLevel, std::string filename);

	void keyCheck();

	bool lostGame() const;

	void lostGameMessage() const;

	bool wonGame() const;

	bool eatFruit(Point& p, Fruit* fruPoint, bool alive);

	void wonGameMessage() const;

	void pauseMessage() const;

	void fileError(int num);

	void clearPauseMessage() const;

	void initGame();

	bool init(std::string filename);

	void getFileArr(std::vector<std::string>& fileArr);

	void loselive();

	void waitForKeyPress() {
		while (!_kbhit()) {}
		// clear buffer
		while (_kbhit()) _getch();
	}
};