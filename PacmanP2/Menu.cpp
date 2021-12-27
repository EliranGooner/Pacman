#include "Menu.h"

Menu::Menu()
{
	srand((unsigned int)time(NULL));

	do
	{
		if (colour)
			setColour(Board::WHITE);
		std::string fileName;

		gotoxy(8, 4);
		std::cout << "(1) " << START_GAME;
		gotoxy(8, 5);
		std::cout << "(2) " << START_COLOUR;
		gotoxy(8, 6);
		std::cout << "(3) " <<  START_SPECIFIC;
		gotoxy(8, 7);
		std::cout << "(8) Present instructions and keys";
		gotoxy(8, 8);
		std::cout << "(9) EXIT" << std::endl;

		changeKey(_getch());

		if (key == KEYS)
		{
			system("CLS");
			std::cout << "Welcome to the Pacman game" << std::endl;
			std::cout << "How do you win?" << std::endl;
			std::cout << "In order to win the Pacman needs to eat all the spreaded breadcrumbs" << std::endl;
			std::cout << "How do you lose?" << std::endl;
			std::cout << "You have 3 lives, if a ghost catches you 3 times the game will be over!" << std::endl;
			std::cout << "Keys: LEFT a or A, RIGHT d or D, UP w or W, Down x or X, STAY s or S" << std::endl;
			std::cout << "Press:" << std::endl;
			std::cout << "(1) " << START_GAME << std::endl;
			std::cout << "(2) " << START_COLOUR << std::endl;
			std::cout << "(3) " << START_SPECIFIC << std::endl;
			std::cout << "(9) EXIT" << std::endl;
			changeKey(_getch());
		}

		system("CLS");

		if (key == SFILE)
		{
			std::cout << "Please enter the name of the requested file" << std::endl;
			std::getline(std::cin, fileName);
			std::ifstream file(fileName, std::ios_base::in);

			if (file.is_open())
			{
				std::cout << "Press:" << std::endl;
				std::cout << "(1) " << START_GAME << std::endl;
				std::cout << "(2) " << START_COLOUR << std::endl;
				changeKey(_getch());
				file.close();
			}

			else
			{
				std::cout << "No file matching this name was found in the directory" << std::endl;
				std::cout << "Press to return to the main menu" << std::endl;
				while (!_kbhit()) {}
				while (_kbhit()) _getch();
			}

		}

		system("CLS");

		if (key == START || key == COLOUR)
		{
			char colourMode = key;
			gotoxy(8, 4);
			std::cout << "(1) Beginner mode";
			gotoxy(8, 5);
			std::cout << "(2) Intermediate mode";
			gotoxy(8, 6);
			std::cout << "(3) Advanced mode";
			changeKey(_getch());

			system("CLS");

			if (colourMode == START)
			{
				colour = false;
				Game start(colour, key, fileName);
			}
			else if (colourMode == COLOUR)
			{
				colour = true;
				Game start(colour, key, fileName);
			}
		}

		system("CLS");

	} while (key != EXIT);

	if (key == EXIT)
	{
		system("CLS");
		std::cout << "GOOD BYE!" << std::endl;
	}
}