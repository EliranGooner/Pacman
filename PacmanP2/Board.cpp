#include "Board.h"

int Board::breadLeft = 0;
int Board::bread = 0;
int Board::extraPoints = 0;

void Board::getRsize(std::ifstream& file)
{
	std::string temp;

	std::getline(file, temp);

	file.seekg(0, file.beg);

	for (int i = 0; i <= temp.size(); i++)
	{
		if (temp[i] == '&')
		{
			max_X = temp.size() + 19;
			return;
		}
	}

	max_X = temp.size();
}

char Board::checkBoardCell(int x, int y) const
{
	if (x < 26 && y < 81)
	{
		if (b[x][y] == '#')
			return WALL;

		if (b[x][y] == '.')
			return CRUMBS;

		else
			return CLEAR;
	}
	else
	{
		return 0;
	}
}

void Board::printBoard(bool colour)const
{
	setColour(WHITE);

	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 81; j++)
		{
			std::cout << b[i][j];
		}
	}
}