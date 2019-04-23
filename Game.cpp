#include <iostream>
#include <stack>
#include <ctime>
using namespace std;
 
enum COLOR {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PINK,
	ORANGE,
	BLACK
};
 
enum NUMBER {
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX
};
 
class Token {
	int countTokens;
	COLOR tokenColor;
}; 
 
class Player {
	int playerId;
	COLOR playerColor;
	Token tokens[4];
};
 
class Dice {
	NUMBER numberOnDice;
};
 
class Game {
	int rowCount;
	int colCount;
	stack<COLOR> *board;
	Dice diceOfGame;
 
	public:
	Game();
	void initializeObstacles();
};
 
Game::Game() {
	rowCount = 6;
	colCount = 9;
	board = new stack<COLOR>[rowCount*colCount];
};
 
void Game::initializeObstacles() {
	srand(time(NULL));
 
	for (int row=0; row < rowCount; row++) {
		int randNum = rand() % 8;
		cout<<(randNum + 1)<<"\n"; // to be removed
 
		int positionOnBoard = (randNum + 1);
		stack<COLOR> stackOnBoard = *(board + (colCount*row) + positionOnBoard); 
		stackOnBoard.push(COLOR::BLACK);
	}
}
 
int main() {
	Game *game = new Game();
	game->initializeObstacles();
	return 0;
  }
