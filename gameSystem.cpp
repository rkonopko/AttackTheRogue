#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "gameSystem.h"
using namespace std;

gameSystem::gameSystem(){

	ifstream in;
	string input, fileName, txt = ".txt";
	char choice;
	int inc = 0;
	
start:
	cout << "Would you like to load a level? (Y/N) ";
	cin >> choice;

	if (choice == 'Y' || choice == 'y'){
		cout << "Type in a level or save name: ";
		cin >> fileName;
		fileName = fileName + txt;
	}
	else if (choice == 'N' || choice == 'n'){
		fileName = "default.txt";
	}
	else{
		cout << "Invalid option";
		goto start;
	}
	
	in.open(fileName);

	if (in.fail())
	{
		perror("Error");
	}
	
	while (getline(in, input)){ 
		level.push_back(input);
	}
}

void gameSystem::levelDisplay(){
	
	system("CLS");
	for (int i = 0; i < level.size(); i++){
		cout << level[i]<<endl;
	}
}

void gameSystem::levelSet(char symbol, int xPos, int yPos){
	
	level[yPos][xPos] = symbol;

}

char gameSystem::levelGet(int xPos, int yPos){

	return level[yPos][xPos];

}

void gameSystem::levelSearch(){
	
	stringstream ss;
	string s = " ", temp = " ";
	int S = 1, R = 1, C = 1, D = 1, P = 1;
	
	for (int y = 0; y < level.size(); y++){
		for (int x = 0; x <= level[0].length(); x++){

			switch (level[y][x]) {
			case '@':
				ss.clear();
				ss << x;
				ss >> s;
				temp = "@";
				temp = temp + " " + s;
				ss.clear();
				ss << y;
				ss >> s;
				temp = temp + " " + s;
				position.push_back(temp);
				break;
			case 'S':
				ss.clear();
				ss << x;
				ss >> s;
				temp = "S";
				temp = temp + " " + s;
				ss.clear();
				ss << y;
				ss >> s;
				temp = temp + " " + s;
				ss.clear();
				ss << S;
				ss >> s;
				temp = temp + " " + s;
				S++;
				position.push_back(temp);
				break;
			case 'R':
				ss.clear();
				ss << x;
				ss >> s;
				temp = "R";
				temp = temp + " " + s;
				ss.clear();
				ss << y;
				ss >> s;
				temp = temp + " " + s;
				ss.clear();
				ss << R;
				ss >> s;
				temp = temp + " " + s;
				R++;
				position.push_back(temp);
				break;
			case 'C':
				ss.clear();
				ss << x;
				ss >> s;
				temp = "C";
				temp = temp + " " + s;
				ss.clear();
				ss << y;
				ss >> s;
				temp = temp + " " + s;
				ss.clear();
				ss << C;
				ss >> s;
				temp = temp + " " + s;
				C++;
				position.push_back(temp);
				break;
			case 'D':
				ss.clear();
				ss << x;
				ss >> s;
				temp = "D";
				temp = temp + " " + s;
				ss.clear();
				ss << y;
				ss >> s;
				temp = temp + " " + s;
				ss.clear();
				ss << D;
				ss >> s;
				temp = temp + " " + s;
				D++;
				position.push_back(temp);
				break;
			case '+':
				ss.clear();
				ss << x;
				ss >> s;
				temp = "+";
				temp = temp + " " + s;
				ss.clear();
				ss << y;
				ss >> s;
				temp = temp + " " + s;
				ss.clear();
				ss << P;
				ss >> s;
				temp = temp + " " + s;
				P++;
				position.push_back(temp);
				break;
			}
		}
	}
	
	for (int i = 0; i < position.size(); i++){
		cout << position[i]<<endl;
		
	}
}

int gameSystem::playerMove(char cmd, int xPos, int yPos){

	switch (cmd) {
		
	case 'w':
		yPos--;
		if (level[yPos][xPos] == '#'){
			return 0;
		}
		else if (level[yPos][xPos] == ' '){
			level[yPos][xPos] = '@';
			yPos++;
			level[yPos][xPos] = ' ';
			return 1;
		}
		else if (level[yPos][xPos] == '+'){
			return 15;
		}
		else if (level[yPos][xPos] == 'R'){
			return 16;
		}
		else if (level[yPos][xPos] == 'S'){
			return 17;
		}
		else if (level[yPos][xPos] == 'C'){
			return 18;
		}
		else if (level[yPos][xPos] == 'D'){
			return 19;
		}
		break;
	
	case 's':
		yPos++;
		if (level[yPos][xPos] == '#'){
			return 0;
		}
		else if (level[yPos][xPos] == ' '){
			level[yPos][xPos] = '@';
			yPos--;
			level[yPos][xPos] = ' ';
			return 2;
		}
		else if (level[yPos][xPos] == '+'){
			return 25;
		}
		else if (level[yPos][xPos] == 'R'){
			return 26;
			break;
		}
		else if (level[yPos][xPos] == 'S'){
			return 27;
		}
		else if (level[yPos][xPos] == 'C'){
			return 28;
		}
		else if (level[yPos][xPos] == 'D'){
			return 29;
		}
		break;
	
	case 'd':
		xPos++;
		if (level[yPos][xPos] == '#'){
			return 0;
		}
		else if (level[yPos][xPos] == ' '){
			level[yPos][xPos] = '@';
			xPos--;
			level[yPos][xPos] = ' ';
			return 3;
		}
		else if (level[yPos][xPos] == '+'){
			return 35;
		}
		else if (level[yPos][xPos] == 'R'){
			return 36;
		}
		else if (level[yPos][xPos] == 'S'){
			return 37;
		}
		else if (level[yPos][xPos] == 'C'){
			return 38;
		}
		else if (level[yPos][xPos] == 'D'){
			return 39;
		}
		break;
	
	case 'a':
		xPos--;
		if (level[yPos][xPos] == '#'){
			return 0;
		}
		else if (level[yPos][xPos] == ' '){
			level[yPos][xPos] = '@';
			xPos++;
			level[yPos][xPos] = ' ';
			return 4;
		}
		else if (level[yPos][xPos] == '+'){
			return 45;
		}
		else if (level[yPos][xPos] == 'R'){
			return 46;
		}
		else if (level[yPos][xPos] == 'S'){
			return 47;
		}
		else if (level[yPos][xPos] == 'C'){
			return 48;
		}
		else if (level[yPos][xPos] == 'D'){
			return 49;
		}
		break;

	default:
		return 0;
		break;
	}
}

int gameSystem::monsterMove(char monster, int xPos, int yPos, int moveA, int moveB, int moveC, int moveD){ // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y--

	//receive monster coordinets and monster move command and change mosnter position, use = level[ypos][xpos] to find out which char needs to be used 

	int inc = 0, move = 4;

	while (inc <= 4){

		inc++;

		if (inc == 1)
			move = moveA;
		
		else if (inc == 2)
			move = moveB;

		else if (inc == 3)
			move = moveC;

		else if (inc == 4)
			move = moveD;

		else
			move = 4;
		
		switch (move){

		case 0:
			xPos++;
			if (level[yPos][xPos] == ' '){
				level[yPos][xPos] = monster;
				xPos--;
				level[yPos][xPos] = ' ';
				return 0;
			}
			xPos--;
			break;

		case 1:
			xPos--;
			if (level[yPos][xPos] == ' '){
				level[yPos][xPos] = monster;
				xPos++;
				level[yPos][xPos] = ' ';
				return 1;
			}
			xPos++;
			break;

		case 2:
			yPos++;
			if (level[yPos][xPos] == ' '){
				level[yPos][xPos] = monster;
				yPos--;
				level[yPos][xPos] = ' ';
				return 2;
			}
			yPos--;
			break;

		case 3:
			yPos--;
			if (level[yPos][xPos] == ' '){
				level[yPos][xPos] = monster;
				yPos++;
				level[yPos][xPos] = ' ';
				return 3;
			}
			yPos++;
			break;
		
		default:
			return 5;
		}
	}
	return 5;
}

void gameSystem::monsterDeath(int xPos, int yPos){
	level[yPos][xPos] = ' ';
}