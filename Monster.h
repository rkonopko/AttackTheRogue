#pragma once
#include <iostream>
#include <string>
using namespace std;

class Monster
{
public:
	Monster(int xPos, int yPos);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

private:
	int _xPos, _yPos;
};

