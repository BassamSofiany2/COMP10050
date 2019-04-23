#include <iostream>
#include <stack>
#include <ctime>
#include <map>
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
 
	public:
	void setColor(COLOR);
};
 
void Player::setColor(COLOR color) {
	playerColor = color;
}
 
class Dice {
	NUMBER numberOnDice;
};
 
class Game {
	int rowCount;
	int colCount;
	int numberOfPlayers;
	Player *players;
	stack<COLOR> *board;
	Dice diceOfGame;
 
	public:
	Game();
	void initializeObstacles();
	void setNumberOfPlayers(int);
	Player *getPlayers();
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
 
void Game::setNumberOfPlayers(int numPlayers) {
	numberOfPlayers = numPlayers;
	players = new Player[numPlayers];
}
 
Player *Game::getPlayers() {
	return players;
}
 
void initializePlayers(Game *game) {
	// Input Number of Players
	int numPlayers;
	do {
		cout<<"Enter the number of players (2-6)\n";
		cin>>numPlayers;
	} while (numPlayers < 2 || numPlayers > 6);
 
	game->setNumberOfPlayers(numPlayers);
 
	// Put all Colors in a map from which players have to pick
	map<COLOR, bool> remainingColors;
	remainingColors[COLOR::RED] = true;
	remainingColors[COLOR::BLUE] = true;
	remainingColors[COLOR::GREEN] = true;
	remainingColors[COLOR::YELLOW] = true;
	remainingColors[COLOR::PINK] = true;
	remainingColors[COLOR::ORANGE] = true;
 
	// Mapping between integer value with Color
	map<int, COLOR> numberColors;
	numberColors.insert(pair<int, COLOR> (1, COLOR::RED));
	numberColors.insert(pair<int, COLOR> (2, COLOR::BLUE));
	numberColors.insert(pair<int, COLOR> (3, COLOR::GREEN));
	numberColors.insert(pair<int, COLOR> (4, COLOR::YELLOW));
	numberColors.insert(pair<int, COLOR> (5, COLOR::PINK));
	numberColors.insert(pair<int, COLOR> (6, COLOR::ORANGE));
 
	// Choose Color for each player
	for (int player=0; player < numPlayers; player++) {
 
		int numberColor = 1;
		int chosenNumberColor;
		bool colorSelectedByPlayer = false;
 
		while (!colorSelectedByPlayer) {
 
			cout<<"Player "<<(player + 1)<<": \n";
			cout<<"Choose your colour"<<"\n";
 
			for (map<COLOR, bool>::iterator it = remainingColors.begin(); it != remainingColors.end(); ++it) {
				if (it->second == true) {
					cout<<numberColor<<" ("<<it->first<<") \n";
				}
				numberColor++;
			}
 
			cout<<"\n";
			cin>>chosenNumberColor;
 
			if (chosenNumberColor < 1 || chosenNumberColor > 6) {
				cout<<"Number Chosen is out of Choice\n";
			} else if (remainingColors[numberColors[chosenNumberColor]] == false) {
				cout<<"Color already taken by another player";
			} else {
				Player *players = game->getPlayers();
				COLOR color = numberColors[chosenNumberColor];
 
				(players[player]).setColor(color);
				remainingColors[color] = false;
				colorSelectedByPlayer = true;
			}
		}
	} 
}
 
int main() {
	// Game Initialization
	Game *game = new Game();
	game->initializeObstacles();
 
	// Player Initialization
	initializePlayers(game);
 
 
 
	return 0;
}
