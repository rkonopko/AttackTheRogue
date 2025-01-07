///////////////////////////////////////////////////////////////////////////////////////
// Attack the Rouge 1.6                                                              //
//                                                                                   //
// By Robert Konopko                                                                 //
//                                                                                   //
// Last Update: 5/21/2018                                                            //
//                                                                                   //
// This game is a rouge like rpg that heavily relies on chance the point of          //
// the game is to defeat the dragon, kill only the dragon for a huge point bonus.    //
// However it's easier to kill enemies and get treasure before fighting the dragon   //
// but you'll get less points. Move with WASD and continue with E.                   //
///////////////////////////////////////////////////////////////////////////////////////

// Have different class monsters fight each other?
// victory and loss notificaiton
// monsters level up when they fight each other
// increment dragon only monster score 100000000 + 1 every time somone wins save in notepad

#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h> 
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include "gameSystem.h"
#include "Monster.h"
#include "Player.h"
using namespace std;

void start();
void cont();
void playerMove(int move);
void allMonsterMove();
int monsterMove(int xPos, int yPos, char monster);
void wEvent();
void sEvent();
void dEvent();
void aEvent();
void gameEvent(char symbol);
void treasureEvent (int treasure);
void battle(char symbol);
int playerBattle(int chance);
int ratBattle(int chance);
int snakeBattle(int chance);
int cyclopsBattle(int chance);
int dragonBattle(int chance);
void smallReward();
void largeReward();
void gameWon();
void gameLoss();

// Setting player and moster positions based on default txt file
// Walls and treasure chests do not need to be set because they are avoided by monsters and interact with the player

gameSystem game;
Player player(4, 2, 30, 0);
Monster rat1(15, 1), rat2(43, 6), rat3(27, 10), rat4(31, 18);
Monster snake1(26, 2), snake2(43, 2), snake3(32, 3), snake4(9, 19);
Monster cyclops(6, 11), dragon(44, 14);

// Setting random number rollers

mt19937 randomGen(time(0));
uniform_int_distribution<int> roll(0, 10);
uniform_int_distribution<int> dRoll(0, 15);
uniform_int_distribution<int> mRoll(0, 3);

bool gameOver = false;


// the mian loop

int main()
{
	
	// set input to 
	char input = ' ';
	start();
	game.levelDisplay();
	player.stats();

	while (gameOver == false){
		input = _getch(); // waits and recieves player input: W A S D or E to continue
		playerMove(game.playerMove(input, player.getX(), player.getY())); // moves player based on input
		game.levelDisplay(); // draws the level
		player.stats();
		allMonsterMove(); 
		game.levelDisplay();
		player.stats();
		if (player.getHealth() <= 0){
			gameOver = true;
		}
	}

	if (player.getHealth() <= 0)
	{
		gameLoss();
	}
	else{
		gameWon();
	}
	return 0;
}

void start(){

	cout << endl << "Welcome to @ttack the Rogue! There are several monsters scattered throughout" << endl
		<< "the map that will attack the player. Use W A S D to move the player," << endl
		<< "the (@) symbol. Fight the weak monsters first so that you have a chance " << endl
		<< "to beat the strong ones. Rats (R) and Snakes (S) are weak, while the " << endl
		<< "Cyclops (C) and the Dragon (D) are strong, fight them last for the best chance " << endl
		<< "to win. However, you can get more points if you only kill the strong ones." << endl
		<< "Defeat the dragon to win the game The (+) symbols are treasure that will" << endl
		<< "help you. If your health falls to 0 it's game over, good luck!" << endl<<endl
		<< "Press the (E) key to attack and to continue." << endl;
	
	cont();
	system("CLS");
}

void cont(){
	char e = ' ';

	do
	{	
		e = _getch();
	} while (e != 'e');
}

void playerMove(int move){ // controls player movement

	int y = 0, x = 0;

	switch (move) {
	case 0: //player doesn't move
		break;
	case 1: //player moves up
		y = player.getY();
		y--;
		player.setY(y);
		break;
	case 2: //player moves down
		y = player.getY();
		y++;
		player.setY(y);
		break;
	case 3: //player moves right
		x = player.getX();
		x++;
		player.setX(x);
		break;
	case 4: //player moves left
		x = player.getX();
		x--;
		player.setX(x);
		break;
	case 15: //W player encounters treasure
		gameEvent('+');
		wEvent();
		break;
	case 25: //S player encounters treasure
		gameEvent('+');
		sEvent();
		break;
	case 35: //D player encounters treasure
		gameEvent('+');
		dEvent();
		break;
	case 45://A player encounters treasure
		gameEvent('+');
		aEvent();
		break;
	case 16: //W player encounters Rat
		gameEvent('R');
		wEvent();
		break;
	case 26: //S player encounters Rat
		gameEvent('R');
		sEvent();
		break;
	case 36: //D player encounters Rat
		gameEvent('R');
		dEvent();
		break;
	case 46://A player encounters Rat
		gameEvent('R');
		aEvent();
		break;
	case 17: //W player encounters Snake
		gameEvent('S');
		wEvent();
		break;
	case 27: //S player encounters Snake
		gameEvent('S');
		sEvent();
		break;
	case 37: //D player encounters Snake
		gameEvent('S');
		dEvent();
		break;
	case 47://A player encounters Snake
		gameEvent('S');
		aEvent();
		break;
	case 18: //W player encounters Cyclops
		gameEvent('C');
		wEvent();
		break;
	case 28: //S player encounters Cyclops
		gameEvent('C');
		sEvent();
		break;
	case 38: //D player encounters Cyclops
		gameEvent('C');
		dEvent();
		break;
	case 48://A player encounters Cyclops
		gameEvent('C');
		aEvent();
		break;
	case 19: //W player encounters Dragon
		gameEvent('D');
		wEvent();
		break;
	case 29: //S player encounters Dragon
		gameEvent('D');
		sEvent();
		break;
	case 39: //D player encounters Dragon
		gameEvent('D');
		dEvent();
		break;
	case 49://A player encounters Dragon
		gameEvent('D');
		aEvent();
		break;
	default:
		break;
	}
}

void allMonsterMove(){ //controls the movemnt of all the monsters

	switch (monsterMove(rat1.getX(), rat1.getY(), 'R')) { 
	
	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		rat1.setX(1);
		break;
	case 1: 
		rat1.setX(-1);
		break;
	case 2: 
		rat1.setY(1);
		break;
	case 3:
		rat1.setY(-1);
		break;
	case 4:
		game.monsterDeath(rat1.getX(),rat1.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(rat2.getX(), rat2.getY(), 'R')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		rat2.setX(1);
		break;
	case 1:
		rat2.setX(-1);
		break;
	case 2:
		rat2.setY(1);
		break;
	case 3:
		rat2.setY(-1);
		break;
	case 4:
		game.monsterDeath(rat2.getX(), rat2.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(rat3.getX(), rat3.getY(), 'R')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		rat3.setX(1);
		break;
	case 1:
		rat3.setX(-1);
		break;
	case 2:
		rat3.setY(1);
		break;
	case 3:
		rat3.setY(-1);
		break;
	case 4:
		game.monsterDeath(rat3.getX(), rat3.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(rat4.getX(), rat4.getY(), 'R')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		rat4.setX(1);
		break;
	case 1:
		rat4.setX(-1);
		break;
	case 2:
		rat4.setY(1);
		break;
	case 3:
		rat4.setY(-1);
		break;
	case 4:
		game.monsterDeath(rat4.getX(), rat4.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(snake1.getX(), snake1.getY(), 'S')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		snake1.setX(1);
		break;
	case 1:
		snake1.setX(-1);
		break;
	case 2:
		snake1.setY(1);
		break;
	case 3:
		snake1.setY(-1);
		break;
	case 4:
		game.monsterDeath(snake1.getX(), snake1.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(snake2.getX(), snake2.getY(), 'S')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		snake2.setX(1);
		break;
	case 1:
		snake2.setX(-1);
		break;
	case 2:
		snake2.setY(1);
		break;
	case 3:
		snake2.setY(-1);
		break;
	case 4:
		game.monsterDeath(snake2.getX(), snake2.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(snake3.getX(), snake3.getY(), 'S')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		snake3.setX(1);
		break;
	case 1:
		snake3.setX(-1);
		break;
	case 2:
		snake3.setY(1);
		break;
	case 3:
		snake3.setY(-1);
		break;
	case 4:
		game.monsterDeath(snake3.getX(), snake3.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(snake4.getX(), snake4.getY(), 'S')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		snake4.setX(1);
		break;
	case 1:
		snake4.setX(-1);
		break;
	case 2:
		snake4.setY(1);
		break;
	case 3:
		snake4.setY(-1);
		break;
	case 4:
		game.monsterDeath(snake4.getX(), snake4.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(cyclops.getX(), cyclops.getY(), 'C')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		cyclops.setX(1);
		break;
	case 1:
		cyclops.setX(-1);
		break;
	case 2:
		cyclops.setY(1);
		break;
	case 3:
		cyclops.setY(-1);
		break;
	case 4:
		game.monsterDeath(cyclops.getX(), cyclops.getY());
		break;
	default:
		break;
	}

	switch (monsterMove(dragon.getX(), dragon.getY(), 'D')) {

	case 0: // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y-- | 4 = dead | 5 = skip/ error
		dragon.setX(1);
		break;
	case 1:
		dragon.setX(-1);
		break;
	case 2:
		dragon.setY(1);
		break;
	case 3:
		dragon.setY(-1);
		break;
	case 4:
		game.monsterDeath(dragon.getX(), dragon.getY());
		break;
	default:
		break;
	}
}

int monsterMove(int xPos, int yPos, char monster){ // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y--

	//subtracts monster coordinates from player coordinates and uses that to decide movment priority, takes the negatives into consideration becasue of the 2d plane used.
	//does all the work in functions here and use gameSystem.monsterMove(x y z etc..) to change the monster position on the map, roll a number as well for random moves. 
	//sends all 4 movement possibilities with priorites in case there is a wall or another monster x++ x-- y++ y--

	int x = 0, y = 0, xa = 0, xb = 0, ya= 0, yb = 0;

	if (game.levelGet(xPos, yPos) == monster){ // Finds the distance between the Monster and Player
		x = player.getX() - xPos;
		y = player.getY() - yPos;

		if (x > 0){
			xa = 0;
			xb = 1;
		}
		else{
			xa = 1;
			xb = 0;
		}

		if (y > 0){
			ya = 2;
			yb = 3;
		}
		else{
			ya = 3;
			yb = 2;
		}


		if (x <= 3 && x >= -3 && y <= 3 && y >= -3){ // if monster is within 3 spaces will follow the player

			if ((x == 1 || x == -1) && y == 0){
				gameEvent(monster);
				if (gameOver == false)
					return 4;
			}
			else if ((y == 1 || y == -1) && x == 0){
				gameEvent(monster);
				if (gameOver == false)
					return 4;
			}
			else if (y == 0){
				if (x < 0)
					return game.monsterMove(monster, xPos, yPos, 1, ya, yb, 0); // 0 = x++ | 1 = x-- | 2 = y++ | 3 = y--
				else
					return game.monsterMove(monster, xPos, yPos, 0, ya, yb, 1);
			}

			else if (x == 0){
				if (y < 0)
					return game.monsterMove(monster, xPos, yPos, 3, xa, xb, 2);
				else
					return game.monsterMove(monster, xPos, yPos, 2, xa, xb, 3);
			}

			else if ((y >= 1 || y <= -1) && (x <= 1 || x >= -1)){  
				if (x > 0)
					return game.monsterMove(monster, xPos, yPos, 0, ya, yb, 1);
				else
					return game.monsterMove(monster, xPos, yPos, 1, ya, yb, 0);
				}

			else if ((x >= 1 || x <= -1) && (y <= 1 || y >= -1)){
				if (y > 0)
					return game.monsterMove(monster, xPos, yPos, 2, xa, xb, 3);
				else
					return game.monsterMove(monster, xPos, yPos, 3, xa, xb, 2);
			}

		}
		
		else{ // If the monster is not near player will move randomly but not into walls or treasure chests

			switch (mRoll(randomGen)) {

			case 0:
				return game.monsterMove(monster, xPos, yPos, 0, 3, 2, 1);
			case 1:
				return game.monsterMove(monster, xPos, yPos, 1, 2, 3, 0);
			case 2:
				return game.monsterMove(monster, xPos, yPos, 2, 1, 0, 3);
			case 3:
				return game.monsterMove(monster, xPos, yPos, 3, 0, 1, 2);
			default:
				break;
			}
		}
	}
	return 5;
}

void wEvent(){
	int y = 0, x = 0;

	y = player.getY();
	x = player.getX();
	game.levelSet(' ', x, y);
	y--;
	player.setY(y);
	game.levelSet('@', x, y);
}

void sEvent(){
	int y = 0, x = 0;

	y = player.getY();
	x = player.getX();
	game.levelSet(' ', x, y);
	y++;
	player.setY(y);
	game.levelSet('@', x, y);
}

void dEvent(){
	int y = 0, x = 0;

	y = player.getY();
	x = player.getX();
	game.levelSet(' ', x, y);
	x++;
	player.setX(x);
	game.levelSet('@', x, y);
}

void aEvent(){
	int y = 0, x = 0;

	y = player.getY();
	x = player.getX();
	game.levelSet(' ', x, y);
	x--;
	player.setX(x);
	game.levelSet('@', x, y);
}

void gameEvent(char symbol){ //decides what happens when players run into monsters or treasure

	switch (symbol) {

	case '+':
		treasureEvent(dRoll(randomGen));
		break;
	case 'R':
		battle('R');
		break;
	case 'S':
		battle('S');
		break;
	case 'C':
		battle('C');
		break;
	case 'D':
		battle('D');
		break;
	default:
		break;
	}

}

void treasureEvent (int treasure){ //controls the bonuses from treasure
	
	switch (treasure) {
	case 0: 
		player.gameScore('+', player.getHealth());
		game.levelDisplay();
		player.stats();
		cout << "The treasure chest is empty" << endl;
		cont();
		break;
	case 1: case 2: case 3: case 4: 
		player.gameScore('+', player.getHealth());
		player.setStrength(2);
		game.levelDisplay();
		player.stats();
		cout << "The treasure chest contains a long sword, strength + 2" << endl;
		cont();
		break;
	case 5: case 6: case 7: case 8: case 9:
		player.gameScore('+', player.getHealth());
		player.setHealth(10);
		game.levelDisplay();
		player.stats();
		cout << "The treasure chest contains a large health potion, health + 10" << endl;
		cont();
		break;
	case 10: case 11: case 12:
		player.gameScore('+', player.getHealth());
		player.setHealth(15);
		game.levelDisplay();
		player.stats();
		cout << "The treasure chest contains master armor, health + 15" << endl;
		cont();
		break;
	case 13: case 14:
		player.gameScore('+', player.getHealth());
		player.setStrength(4);
		game.levelDisplay();
		player.stats();
		cout << "The treasure chest contains a greatsword, strength + 4" << endl;
		cont();
		break;
	case 15:
		player.gameScore('+', player.getHealth());
		player.setHealth(-30);
		game.levelDisplay();
		player.stats();
		cout << "Oh no the treasure chest is a mimic! it does 30 damage" << endl;
		cont();
		break;

	default:
		break;
	}
}

// Monster health values switch to balancer monster health
// Monster start battle message
// Battle Controller

void battle(char symbol){

	int P = 0, R = 12, S = 15, C = 31, D = 51;  // Health values 
	P = player.getHealth();
	
	switch (symbol) {
	case 'R':
		cout << "You have run into a Rat prepare for battle!" << endl;
		cont();
		while (P > 0 && R > 0){
			R = R - playerBattle(roll(randomGen));
			if (R <= 0){
				break;
			}
			P = P - ratBattle(roll(randomGen));
			player.setHealth((player.getHealth() - P) * -1);
		}
		break;
	case 'S':
		cout << "A Snake lunges at you prepare for battle!" << endl;
		cont();
		while (P > 0 && S > 0){
			S = S - playerBattle(roll(randomGen));
			if (S <= 0){
				break;
			}
			P = P - snakeBattle(roll(randomGen));
			player.setHealth((player.getHealth() - P) * -1);
		}
		break;
	case 'C':
		cout << "You hear loud stomping, is it the neighbors?! No it's a Cyclops!" << endl << "Prepare for battle." << endl;
		cont();
		while (P > 0 && C > 0){
			C = C - playerBattle(roll(randomGen));
			if (C <= 0){
				break;
			}
			P = P - cyclopsBattle(roll(randomGen));
			player.setHealth((player.getHealth() - P) * -1);
		}
		break;
	case 'D':
		cout << "You hear a loud screech and look up, a drgaon swoops in and lands in" << endl << "front of you, this is it. Prepare for battle." << endl;
		cont();
		while (P > 0 && D > 0){
			D = D - playerBattle(roll(randomGen));
			if (D <= 0){
				break;
			}
			P = P - dragonBattle(dRoll(randomGen));
			player.setHealth((player.getHealth() - P) * -1);
		}
		break;
	default:
		break;
	}

	if (P <= 0){
		player.setHealth(P);
		cout << "You have died!" << endl
			<< "Game over" << endl;
		cont();
		gameOver = true;
	}
	else if (R <= 0){
		P = (player.getHealth() - P) * -1;
		player.setHealth(P);
		cout << "The rat is defeated" << endl;
		cont();
		smallReward();
		player.gameScore('R', player.getHealth());
	}
	else if (S <= 0){
		P = (player.getHealth() - P) * -1;
		player.setHealth(P);
		cout << "The snake shrivels and dies" << endl;
		cont();
		smallReward();
		player.gameScore('S', player.getHealth());
	}
	else if (C <= 0){
		P = (player.getHealth() - P) * -1;
		player.setHealth(P);
		cout << "Victory!, The Cyclops falls to his knees, and his eye falls from his head" << endl;
		cont();
		largeReward();
		player.gameScore('C', player.getHealth());
	}
	else if (D <= 0){
		P = (player.getHealth() - P) * -1;
		player.setHealth(P);
		cout << "The Dragon falls, fire spewing from its mouth, and as the fire fades into " << endl
			 << "an ember you see the dragon weaknen and die. You feel the joy of victory, " << endl
			 << "but you know there is more to be done. You leave this place and move further." << endl;
		cont();
		player.gameScore('D', player.getHealth());
		gameOver = true;
	}
	else
		cout << "error";
}

int playerBattle(int chance){
	
	switch (chance) {
	case 0: 
		game.levelDisplay();
		player.stats();
		cout << "You missed 0 damage dealt" << endl;
		cont();
		return 0;
		break;
	case 1: case 2: case 3: case 4: case 5: case 6:
		game.levelDisplay();
		player.stats();
		cout << "You strike the enemy with your sword, you deal "<< 5 + player.getStrength() << " Damage" << endl;
		cont();
		return 5 + player.getStrength();
		break;
	case 7: case 8: case 9: 
		game.levelDisplay();
		player.stats();
		cout << "You preform a jumping attack with your sword, you deal " << 7 + player.getStrength() << " Damage" << endl;
		cont();
		return 7 + player.getStrength();
		break;
	case 10:
		game.levelDisplay();
		player.stats();
		cout << "You channel all your energy into a powerful spell, you deal " << 10 + player.getStrength() << " Damage" << endl;
		cont();
		return 12 + player.getStrength();
		break;
	default:
		break;
	}
}

int ratBattle(int chance){

	switch (chance) {
	case 0: case 1:
		game.levelDisplay();
		player.stats();
		cout << "The Rat missed 0 damage taken" << endl;
		cont();
		return 0;
		break;
	case 2: case 3: case 4: case 5: case 6:
		game.levelDisplay();
		player.stats();
		cout << "The Rat bites you, it does 3 damage" << endl;
		cont();
		return 3;
		break;
	case 7: case 8: case 9: 
		game.levelDisplay();
		player.stats();
		cout << "The Rat scratches you, it does 5 damage" << endl;
		cont();
		return 5;
		break;
	case 10:
		game.levelDisplay();
		player.stats();
		cout << "The Rat's eyes start to glow red it unleashes a flurry of attacks," << endl << "it deals 10 damage" << endl;
		cont();
		return 10;
		break;
	default:
		break;
	}
}

int snakeBattle(int chance){

	switch (chance) {
	case 0: 
		game.levelDisplay();
		player.stats();
		cout << "The Snake missed 0 damage taken" << endl;
		cont();
		return 0;
		break;
	case 1: case 2: case 3: case 4: case 5: 
		game.levelDisplay();
		player.stats();
		cout << "The Snake hits you with his tail, it does 4 damage" << endl;
		cont();
		return 4;
		break;
	case 6: case 7: case 8: case 9:
		game.levelDisplay();
		player.stats();
		cout << "The Snake bites you, it's venom stings 6 damage taken" << endl;
		cont();
		return 6;
		break;
	case 10:
		game.levelDisplay();
		player.stats();
		cout << "The Snake starts to shake violently, it spits acid at you!" << endl << "it deals 15 damage" << endl;
		cont();
		return 15;
		break;
	default:
		break;
	}
}

int cyclopsBattle(int chance){

	switch (chance) {
	case 0:
		game.levelDisplay();
		player.stats();
		cout << "The Cyclops missed 0 damage taken" << endl;
		cont();
		return 0;
		break;
	case 1: case 2: case 3: case 4: case 5:
		game.levelDisplay();
		player.stats();
		cout << "The Cyclops stomps on you, it does 6 damage" << endl;
		cont();
		return 6;
		break;
	case 6: case 7: case 8: case 9:
		game.levelDisplay();
		player.stats();
		cout << "The Cyclops smashes you with its club 10 damage taken" << endl;
		cont();
		return 10;
		break;
	case 10:
		game.levelDisplay();
		player.stats();
		cout << "The Cyclops bellows a war cry and lunges into the air, he comes crashing down" << endl << "on top of you with his club, it deals 18 damage" << endl;
		cont();
		return 18;
		break;
	default:
		break;
	}
}

int dragonBattle(int chance){

	switch (chance) {
	case 0:
		game.levelDisplay();
		player.stats();
		cout << "The Dragon missed 0 damage taken" << endl;
		cont();
		return 0;
		break;
	case 1: case 2: case 3: case 4: case 5:
		game.levelDisplay();
		player.stats();
		cout << "The Dragon swipes at you with its claws, it does 9 damage" << endl;
		cont();
		return 9;
		break;
	case 6: case 7: case 8: case 9: case 10:
		game.levelDisplay();
		player.stats();
		cout << "The Dragon hits you with its tail, 10 damage taken" << endl;
		cont();
		return 10;
		break;
	case 11:  case 12:
		game.levelDisplay();
		player.stats();
		cout << "The Dragon flys into the air, circles around, and swoops down right" << endl << "into you, it deals 15 damage" << endl;
		cont();
		return 15;
		break;
	case 13:  case 14:
		game.levelDisplay();
		player.stats();
		cout << "The Dragon shoots out a fireball at you dealing 14 damage" << endl;
		cont();
		return 14;
		break;
	case 15:
		game.levelDisplay();
		player.stats();
		cout << "The Dragon flies into the air and starts breathing out fire, he flys towards" << endl << "you. You try to run but the flames engulf you, 25 damage taken" << endl;
		cont();
		return 25;
		break;
	default:
		break;
	}
}

void smallReward(){

	switch (roll(randomGen)){
	case 0:
		game.levelDisplay();
		player.stats();
		cout << "The enemy dropped nothing" << endl;
		cont();
		break;
	case 1: case 2: case 3: case 4: case 5:
		player.setHealth(5);
		game.levelDisplay();
		player.stats();
		cout << "The enemy dropped a potion, health + 5" << endl;
		cont();
		break;
	case 6: case 7: case 8: case 9: 
		player.setStrength(1);
		game.levelDisplay();
		player.stats();
		cout << "You gained experince from that fight strength + 1" << endl;
		cont();
		break;
	case 10:
		player.setStrength(1);
		player.setHealth(10);
		game.levelDisplay();
		player.stats();
		cout << "The enemy dropped a large potion, health + 10, and you gained experince"<< endl << "from that fight, strength + 1" << endl;
		cont();
	}
}

void largeReward(){

	switch (roll(randomGen)){
	case 0:
		game.levelDisplay();
		player.stats();
		cout << "The Cyclops dropped nothing" << endl;
		cont();
		break;
	case 1: case 2: case 3: case 4: case 5:
		player.setHealth(15);
		game.levelDisplay();
		player.stats();
		cout << "The Cyclops dropped a shield, health + 15" << endl;
		cont();
		break;
	case 6: case 7: case 8: case 9:
		player.setStrength(5);
		game.levelDisplay();
		player.stats();
		cout << "The Cyclops dropped his great club, strength + 5" << endl;
		cont();
		break;
	case 10:
		player.setStrength(4);
		player.setHealth(15);
		game.levelDisplay();
		player.stats();
		cout << "You rip out the Cyclops's eye and crush it, power surges through you granting" << endl << "you strength and health, strength + 5, health + 15." << endl;
		cont();
	}
}

void gameWon(){
	cout << "Congrats you won!" << endl
		 << "your final score is: " << player.getScore() << endl;
	cont();
}

void gameLoss(){
	player.setDeath();
	game.levelDisplay();
	player.stats();
	cout << "game over you lost" << endl
		 << "your final score is: " << player.getScore() << endl;
	cont();
}

/*void saveLevel(){ //what a save

	ofstream out;
	string fileName, txt = ".txt";

	cout << "Create a save name: ";
	cin >> fileName;

	fileName = fileName + txt;

	out.open(fileName);

	if (out.fail())
	{
	perror("error");
	}

	out << "Vector"; //need to write the vector to file, line by line?
	out.close();

}
*/

/*
@ = player 
S = snake
R = rat 
C = cyclops
D = dragon
*/