#include "Ghost.h"

void Ghost::init(char dir)
{
	getPoint().updateX(startX);
	getPoint().updateY(startY);
	getPoint().changeDir(dir);
	getPoint().draw('$');
}

void Ghost::move(Board& b)
{
	bool clear = FALSE;

	if (b.checkBoardCell(getPoint().getY(), getPoint().getX()) == Board::CRUMBS)
		getPoint().draw('.');
	else
		getPoint().erase();

	while (!getPoint().nextPoint(b))
	{
		getPoint().changeDir(randDirection());
	}

	getPoint().draw(getPoint().getFig());
}