#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class gameSystem
{
public:
	gameSystem();
	void levelDisplay();
	void levelSet(char symbol, int xPos, int yPos);
	char levelGet(int xPos, int yPos);
	void levelSearch();
	int playerMove(char cmd, int xPos, int yPos);
	int monsterMove(char monster, int xPos, int yPos, int moveA, int moveB, int moveC, int moveD);
	void monsterDeath(int xPos, int yPos);

private:
	vector<string> level;
	vector<string> position;
};

