#include "Point.h"

bool Point::nextPoint(Board& b)
{
	bool clear = false;

	switch (dir) {

	case LEFT:
	case 'A':
		if (x == 0 && b.checkBoardCell(y, x) != Board::WALL && b.checkBoardCell(y, b.getmaxX() - 1) != Board::WALL)
		{
			if (figure == Point::PACMAN)
			{
				updateX(b.getmaxX() - 1);
				clear = TRUE;
			}

			if (figure == Point::GHOST || ifFruit() == true)
				break;
		}

		else if (b.checkBoardCell(y, x - 1) != Board::WALL && x > 0)
		{
			updateX(x - 1);
			clear = TRUE;
		}
		break;

	case RIGHT:
	case 'D':
		if (x == b.getmaxX() - 1 && b.checkBoardCell(y, x) != Board::WALL && b.checkBoardCell(y, 0) != Board::WALL)
		{
			if (figure == Point::PACMAN)
			{
				updateX(0);
				clear = TRUE;
			}

			if (figure == Point::GHOST || ifFruit() == true)
				break;
		}

		if (b.checkBoardCell(y, x + 1) != Board::WALL && x < b.getmaxX() - 1)
		{
			updateX(x + 1);
			clear = TRUE;
		}
		break;

	case UP:
	case 'W':
		if (y == 0 && b.checkBoardCell(y, x) != Board::WALL && b.checkBoardCell(b.getmaxY() - 1, x) != Board::WALL)
		{
			if (figure == Point::PACMAN)
			{
				updateY(b.getmaxY() + 1);
				clear = TRUE;
			}

			if (figure == Point::GHOST || ifFruit() == true)
				break;
		}

		if (b.checkBoardCell(y - 1, x) != Board::WALL && y > 0)
		{
			updateY(y - 1);
			clear = TRUE;
		}
		break;

	case DOWN:
	case 'X':
		if (y == b.getmaxY() - 1 && b.checkBoardCell(y, x) != Board::WALL && b.checkBoardCell(0, x) != Board::WALL)
		{
			if (figure == Point::PACMAN)
			{
				updateY(0);
				clear = TRUE;
			}

			if (figure == Point::GHOST || ifFruit() == true)
				break;
		}

		if (b.checkBoardCell(y + 1, x) != Board::WALL && y < b.getmaxY() - 1)
		{
			updateY(y + 1);
			clear = TRUE;
		}

		break;

	case STAY:
	case 'S':
		break;
	}

	if (!clear)
		return false;
}

void Point::randFigure(Board& b)
{
	figure = (rand() % (9 - 5 + 1) + 5) + '0';
}

void Point::randPoint(Board& b)
{
	bool flug = TRUE;

	do {
		flug = TRUE;

		x = rand() % b.getmaxX();

		y = rand() % b.getmaxY();

		if (b.checkBoardCell(y, x) == Board::WALL)
		{
			flug = FALSE;
		}

		if (x >= b.getLivesX() && x <= b.getLivesX() + 20 && y >= b.getLivesY() && y <= b.getLivesY() + 3)
		{
			flug = FALSE;
		}

	} while (flug == FALSE);
}

void Point::draw(char figure1) const
{
	gotoxy(x, y);

	if (colour)
	{
		if (figure1 == '@')
			setColour(Board::YELLOW);
		else if (figure1 == '$')
			setColour(Board::BLUE);
		else if (figure1 >= '5' && figure1 <= '9')
			setColour(Board::RED);
		else
			setColour(Board::WHITE);
	}
	std::cout << figure1;
}

void Point::chaseMode(const Point& pacPoint, const Board& b)
{
	int i, j, minDistRight = -1, minDistLeft = -1, minDistUp = -1, minDistDown = -1, minDist = 0;
	char temp, dir, gridTemp;
	int pacX = pacPoint.getX();
	int pacY = pacPoint.getY();
	char grid[25][80] = {};

	for (i = 0; i < 25; i++) {
		for (j = 0; j < 80; j++)
		{
			if (b.checkBoardCell(i, j) == Board::WALL)
				grid[i][j] = '#';
			else
				grid[i][j] = ' ';
		}
	}

	grid[pacY][pacX] = '@';
	grid[y][x] = '$';

	gridTemp = grid[y + 1][x];
	gridTemp = grid[y - 1][x];
	gridTemp = grid[y][x + 1];
	gridTemp = grid[y][x - 1];

	if (grid[y + 1][x] == grid[pacY][pacX])
	{
		changeDir(DOWN);
		return;
	}
	else if (grid[y + 1][x] != '#')
	{
		temp = grid[y + 1][x];
		grid[y + 1][x] = grid[y][x];
		grid[y][x] = '#';
		minDistDown = minDistance(grid);
		grid[y + 1][x] = temp;
		grid[y][x] = '$';
	}

	if (grid[y][x - 1] == grid[pacY][pacX])
	{
		changeDir(LEFT);
		return;
	}
	else if (grid[y][x - 1] != '#')
	{
		temp = grid[y][x - 1];
		grid[y][x - 1] = grid[y][x];
		grid[y][x] = '#';
		minDistLeft = minDistance(grid);
		grid[y][x - 1] = temp;
		grid[y][x] = '$';
	}

	if (grid[y - 1][x] == grid[pacY][pacX])
	{
		changeDir(UP);
		return;
	}
	else if (grid[y - 1][x] != '#')
	{
		temp = grid[y - 1][x];
		grid[y - 1][x] = grid[y][x];
		grid[y][x] = '#';
		minDistUp = minDistance(grid);
		grid[y - 1][x] = temp;
		grid[y][x] = '$';
	}

	if (grid[y][x + 1] == grid[pacY][pacX])
	{
		changeDir(RIGHT);
		return;
	}
	if (grid[y][x + 1] != '#')
	{
		temp = grid[y][x + 1];
		grid[y][x + 1] = grid[y][x];
		grid[y][x] = '#';
		minDistRight = minDistance(grid);
		grid[y][x + 1] = temp;
		grid[y][x] = '$';
	}

	minDist = max(max(minDistLeft, minDistRight), max(minDistUp, minDistDown));
	if (minDistRight <= minDist && minDistRight != -1)
	{
		minDist = minDistRight;
		dir = RIGHT;
	}
	if (minDistLeft <= minDist && minDistLeft != -1)
	{
		minDist = minDistLeft;
		dir = LEFT;
	}
	if (minDistUp <= minDist && minDistUp != -1)
	{
		minDist = minDistUp;
		dir = UP;
	}
	if (minDistDown <= minDist && minDistDown != -1)
	{
		minDist = minDistDown;
		dir = DOWN;
	}

	changeDir(dir);
}

int Point::minDistance(char grid[25][80])
{
	QItem source(0, 0, 0);

	bool visited[25][80] = {};

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 80; j++)
		{
			if (grid[i][j] == '#')
				visited[i][j] = true;
			else
				visited[i][j] = false;

			if (grid[i][j] == '$')
			{
				source.row = i;
				source.col = j;
			}
		}
	}

	std::queue<QItem> q;
	q.push(source);
	visited[source.row][source.col] = true;
	while (!q.empty()) {
		QItem p = q.front();
		q.pop();

		if (grid[p.row][p.col] == '@')
			return p.dist;

		if (p.row - 1 >= 0 && visited[p.row - 1][p.col] == false)
		{
			q.push(QItem(p.row - 1, p.col, p.dist + 1));
			visited[p.row - 1][p.col] = true;
		}

		if (p.row + 1 < 25 && visited[p.row + 1][p.col] == false)
		{
			q.push(QItem(p.row + 1, p.col, p.dist + 1));
			visited[p.row + 1][p.col] = true;
		}

		if (p.col - 1 >= 0 && visited[p.row][p.col - 1] == false)
		{
			q.push(QItem(p.row, p.col - 1, p.dist + 1));
			visited[p.row][p.col - 1] = true;
		}

		if (p.col + 1 < 80 && visited[p.row][p.col + 1] == false)
		{
			q.push(QItem(p.row, p.col + 1, p.dist + 1));
			visited[p.row][p.col + 1] = true;
		}
	}
	return -1;
}