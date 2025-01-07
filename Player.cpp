#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(int xPos, int yPos, int health, int strength)
{
	_xPos = xPos;
	_yPos = yPos;
	_health = health;
	_strength = strength;
}

void Player::setDeath()
{
	_health = 0;
}

int Player::getX()
{
	return _xPos;
}

int Player::getY()
{
	return _yPos;
}

void Player::setX(int x)
{
	_xPos = x;
}

void Player::setY(int y)
{
	_yPos = y;
}

int Player::getHealth()
{
	return _health;
}

void Player::setHealth(int health)
{
	_health = _health + health;
}

int Player::getStrength()
{
	return _strength;
}

void Player::setStrength(int strength)
{
	_strength = _strength + strength;
}

void Player::stats()
{
	cout << "Health: " << _health << " " << "Strength: " << _strength << " " << "Score: " << _score << endl;
}

void Player::gameScore(char monster, int playerHealth){

	switch (monster) {

	case '+':
		_score = _score - 50;
		break;

	case 'R':
		_score = _score + 100;
		_score = _score + (playerHealth * 5);
		_monsterScore++;
		break;

	case 'S':
		_score = _score + 150;
		_score = _score + (playerHealth * 5);
		_monsterScore++;
		break;

	case 'C':
		_score = _score + 500;
		_score = _score + (playerHealth * 7);
		_monsterScore++;
		break;

	case 'D':
		_score = _score + 1000;
		if (_monsterScore == 0){

			//incremant this!! and save with notepad file

			_score = _score + 1000000000;
			_score = _score + (playerHealth * 15);
			
			break;
		}
		else{
			_score = _score + (playerHealth * 10);
			break;
		}

	default:
		break;
	}
}

int Player::getScore(){

	_score = _score - (_monsterScore * _monsterScore * 20);
	return _score;
}
