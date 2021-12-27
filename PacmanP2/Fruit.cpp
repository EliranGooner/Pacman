#include "Fruit.h"

void Fruit::move(Board& b)
{
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