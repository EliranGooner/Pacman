#pragma once
#include "Game.h"
#include "General.h"

// Handles the menu, prints it to the user and directs the user to appropriate feature.
class Menu
{
	char key;
	bool colour = false;
public:
	enum { START = '1', COLOUR = '2', SFILE = '3', KEYS = '8', EXIT = '9' };
	const std::string START_GAME = "Start game";
	const std::string START_COLOUR = "Start game with colours";
	const std::string START_SPECIFIC = "Start game with a specific file";
	Menu();
	void changeKey(char _key) { key = _key; };
};