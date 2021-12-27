#include "Pacman.h"

int Pacman::lives = 3;

void Pacman::init()
{
	getPoint().updateX(startX);
	getPoint().updateY(startY);
	getPoint().changeDir('s');
	getPoint().draw('@');
}

void Pacman::move(Board& b)
{
	bool clear = FALSE;

	if (b.checkBoardCell(getPoint().getY(), getPoint().getX()) == Board::CRUMBS)
	{
		b.eatBread(getPoint().getY(), getPoint().getX());
		b.showPoints(colour);
	}

	getPoint().erase();

	if (!getPoint().nextPoint(b))
		getPoint().changeDir(Point::STAY);

	getPoint().draw(getPoint().getFig());
}