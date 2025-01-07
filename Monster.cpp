#include "Monster.h"
#include <iostream>
#include <string>
using namespace std;

Monster::Monster(int xPos, int yPos)
{
	_xPos = xPos;
	_yPos = yPos;
}

int Monster::getX()
{
	return _xPos;
}

int Monster::getY()
{
	return _yPos;
}

void Monster::setX(int x)
{
	_xPos = _xPos + x;
}

void Monster::setY(int y)
{
	_yPos = _yPos + y;
}