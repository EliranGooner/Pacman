#include "Creature.h"

Creature::Creature(int _startX, int _startY, char _figure, bool _colour, char _dir, char _gameMode) : startX(_startX), startY(_startY), colour(_colour)
{
	p = Point(startX, startY, _figure, _colour, _dir, _gameMode);
}

Creature::Creature(Board& b, bool _colour)
{
	p = Point(b, _colour);
}