#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player
{
public:
	Player(int xPos, int yPos, int health, int strength);
	void setDeath();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getHealth();
	void setHealth(int health);
	int getStrength();
	void setStrength(int strength);
	void stats();
	void gameScore(char monster, int playerHealth);
	int getScore();

private:
	int _xPos, _yPos, _health, _strength, _score = 0, _monsterScore = 0;
};

