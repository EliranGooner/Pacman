#include "Game.h"
bool Game::init(std::string filename)
{
	b = {};
	std::ifstream file(filename, std::ios_base::in);
	int countPac = 0;
	numOfGhosts = 0;
	char ch;
	int j = 0;
	b.getRsize(file);

	if (b.getmaxX() == 0)
	{
		fileError(2);
		return false;
	}

	while (!file.eof())
	{
		for (int i = 0; i < b.getmaxX(); i++)
		{
			ch = file.get();

			if (ch == ' ')
			{
				b.upDateCell(j, i, '.');
				b.UpdateBread();
			}

			else if (ch == '@')
			{
				countPac++;
				pac = Pacman(i, j, colour);
				b.upDateCell(j, i, '.');
				b.UpdateBread();
			}

			else if (ch == '%')
			{
				b.upDateCell(j, i, ' ');
			}

			else if (ch == '$')
			{
				ghosts[numOfGhosts] = Ghost(i, j, colour, '$', gameLevel);
				b.upDateCell(j, i, '.');
				b.UpdateBread();
				numOfGhosts++;
			}

			else if (ch == '\n' && i < b.getmaxX())
			{
				for (int k = i; k < b.getmaxX(); k++)
				{
					b.upDateCell(j, k, '.');
					b.UpdateBread();
				}
				i = b.getmaxX() + 1;
			}

			else if (ch == '\n' && i == b.getmaxX())
			{
				b.upDateCell(j, i, '\n');
			}

			else if (ch == '&')
			{
				b.UpdateLivesX(i);
				b.UpdatelivesY(j);
			}

			else
				b.upDateCell(j, i, ch);
		}

		ch = file.get();

		b.upDateCell(j, 80, '\n');

		while (ch != '\n' && !file.eof() && j != 0)
		{
			ch = file.get();
		}

		j++;
	}

	if (countPac != 1)
	{
		fileError(3);
		return false;
	}

	if (b.getLivesY() + 2 < j - 1)
		b.UpdateMaxY(j - 1);

	else
		b.UpdateMaxY(b.getLivesY() + 2);

	for (int i = b.getLivesY(); i < b.getLivesY() + 3; i++)
	{
		for (int k = b.getLivesX(); k < b.getLivesX() + 20; k++)
		{
			if (b.checkBoardCell(i, k) == Board::CRUMBS)
				b.removeBread();

			b.upDateCell(i, k, ' ');
		}
	}

	b.printBoard(colour);

	return true;
}

void Game::initGame()
{
	for (int i = 0; i < numOfGhosts; i++)
	{
		if (b.checkBoardCell(ghosts[i].getPoint().getY(), ghosts[i].getPoint().getX()) == Board::CRUMBS)
			ghosts[i].getPoint().draw('.');
		else
			ghosts[i].getPoint().draw(' ');
	}

	pac.init();

	for (int i = 0; i < numOfGhosts; i++)
	{
		ghosts[i].init();
	}
}

void Game::keyCheck()
{
	char currDir;

	if (_kbhit())
	{
		currDir = _getch();

		if (currDir == 27)
		{
			pause = !pause;
			clearPauseMessage();
		}

		if (currDir == 'w' || currDir == 'W' || currDir == 'x' || currDir == 'X' || currDir == 'a' || currDir == 'A' || currDir == 'd' || currDir == 'D' || currDir == 's' || currDir == 'S')
		{
			pac.getPoint().changeDir(currDir);
		}
	}
}

void Game::pauseMessage() const
{
	gotoxy(8, 23);
	if (colour)
		setColour(Board::WHITE);
	std::cout << "Game paused, press ESC to continue";
}

void Game::clearPauseMessage() const
{
	int i;
	for (i = 8; i <= 43; i++)
	{
		gotoxy(i, 23);
		std::cout << " ";
	}
}

bool Game::wonGame() const
{
	if (b.getBreadLeft() == b.getBread())
	{
		return true;
	}

	return false;
}

bool Game::lostGame() const
{
	if (pac.getlives() == 0)
	{
		return true;
	}

	return false;
}

void Game::loselive()
{
	for (int i = 0; i < numOfGhosts; i++)
	{
		if (pac.getPoint().getX() == ghosts[i].getPoint().getX() && pac.getPoint().getY() == ghosts[i].getPoint().getY())
		{
			initGame();
			pac.decreaseLife();
		}
	}

	pac.showLives(b.getLivesX(), b.getLivesY(), colour);
}

void Game::lostGameMessage() const
{
	system("CLS");
	gotoxy(10, 10);
	if (colour)
		setColour(Board::RED);
	std::cout << "GAME OVER!" << std::endl;
	std::cout << "Press any key to return to main menu" << std::endl;
	while (!_kbhit()) {}
	// clear buffer
	while (_kbhit()) _getch();
}

void Game::wonGameMessage() const
{
	system("CLS");
	gotoxy(10, 10);
	if (colour)
		setColour(Board::YELLOW);
	std::cout << "YOU WON!" << std::endl;
	std::cout << "Press any key to return to main menu" << std::endl;
	while (!_kbhit()) {}
	// clear buffer
	while (_kbhit()) _getch();
}

void Game::fileError(int num)
{
	if (colour)
		setColour(Board::WHITE);
	if (num == 1)
	{
		std::cout << "No files found" << std::endl;
		std::cout << "Press any key to return to main menu" << std::endl;
	}
	else if (num == 2)
	{
		std::cout << "The file is empty" << std::endl;
		std::cout << "Press any key to continue" << std::endl;
	}
	else
	{
		std::cout << "The file is invalid, there should be one Pacman on the game board" << std::endl;
		std::cout << "Press any key to continue" << std::endl;
	}
	waitForKeyPress();
	system("CLS");
}

void Game::getFileArr(std::vector<std::string>& fileArr)
{
	std::string pathStr;

	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
	{
		pathStr = entry.path().filename().u8string();
		if (pathStr.size() > 7 && pathStr.size() - 7 == pathStr.rfind(".screen"))
			fileArr.push_back(pathStr);

	}

	std::sort(fileArr.begin(), fileArr.end());
}

bool Game::eatFruit(Point& p, Fruit* fru, bool alive)
{
	if (alive)
	{
		if (p.getFig() == Point::GHOST && p.getX() == fru->getPoint().getX() && p.getY() == fru->getPoint().getY())
		{
			delete fru;
			return false;
		}

		else if (p.getFig() == Point::PACMAN && p.getX() == fru->getPoint().getX() && p.getY() == fru->getPoint().getY())
		{
			b.upDatefuitP(fru->getPoint().getFig() - '0');
			delete fru;
			b.showPoints(colour);
			return false;
		}

		return true;
	}
}

Game::Game(bool _colour, char _gameLevel, std::string filename) : colour(_colour), gameLevel(_gameLevel)
{
	std::vector<std::string> fileArr;
	int ghostMoveCounter = 0;
	bool frulive = false;

	if (filename.size() == 0)
		getFileArr(fileArr);
	else
		fileArr.push_back(filename);

	for (unsigned int i = 0; i < fileArr.size() && !lostGame(); i++)
	{
		if (init(fileArr[i]))
		{
			while (!lostGame() && !wonGame())
			{
				keyCheck();

				if (!pause)
				{
					if (rand() % 6 == 2)
					{
						if (!frulive)
						{
							fru = new Fruit(b, colour);
							frulive = true;
						}

						else
						{
							if (b.checkBoardCell(fru->getPoint().getY(), fru->getPoint().getX()) == Board::CRUMBS)
								fru->getPoint().draw('.');
							else
								fru->getPoint().draw(' ');
							delete fru;
							frulive = false;
						}
					}

					if (frulive)
						fru->move(b);

					frulive = eatFruit(pac.getPoint(), fru, frulive);

					pac.move(b);
					//frulive = eatFruit(pac.getPoint(), fru, frulive);
					loselive();

					for (int i = 0; i < numOfGhosts; i++)
					{
						if (gameLevel == Board::ADVANCED)
						{
							ghosts[i].getPoint().chaseMode(pac.getPoint(), b);
						}
						else
						{
							if (ghostMoveCounter == 20)
							{
								ghosts[i].getPoint().changeDir(randDirection());
								ghostMoveCounter = 0;
							}
							if (ghostMoveCounter >= 5 && gameLevel == Board::INTERMEDIATE)
								ghosts[i].getPoint().chaseMode(pac.getPoint(), b);
						}

						ghosts[i].move(b);
						frulive = eatFruit(pac.getPoint(), fru, frulive);
						loselive();
					}

					ghostMoveCounter++;
					Sleep(200);
					keyCheck();
					pac.move(b);
					//frulive = eatFruit(pac.getPoint(), fru, frulive);
					loselive();
					Sleep(200);
				}
				else
					pauseMessage();
			}

			if (lostGame())
			{
				b.initBread();
				pac.initlives();
				lostGameMessage();
				return;
			}

			if (wonGame())
			{
				wonGameMessage();
				system("CLS");
			}
		}
	}

	b.initBread();
	pac.initlives();

	if (fileArr.size() == 0)
	{
		fileError(1);
		return;
	}
}