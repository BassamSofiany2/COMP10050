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
	int tokenId; 
	COLOR tokenColor;
	
	public:
	void setTokenId(int);
	int getTokenId();
	void setTokenColor(COLOR);
	COLOR getTokenColor();
}; 

void Token::setTokenId(int id) {
	tokenId = id;
}

int Token::getTokenId() {
	return tokenId;
}

void Token::setTokenColor(COLOR color) {
	tokenColor = color;
}

COLOR Token::getTokenColor() {
	return tokenColor;
}

class Player {
	int playerId;
	COLOR playerColor;
	Token *tokens;
	
	public:
	void setColor(COLOR);
	COLOR getColor();
	void setPlayerId(int);
	int getPlayerId();
	void setTokens();
	Token *getTokens();
};

void Player::setColor(COLOR color) {
	playerColor = color;
}

COLOR Player::getColor() {
	return playerColor;
}

void Player::setPlayerId(int id) {
	playerId = id;
}

int Player::getPlayerId() {
	return playerId;
}

void Player::setTokens() {
	int tokensCount = 4;
	tokens = new Token[tokensCount];
	for (int count=0; count < tokensCount; ++count) {
		tokens[count].setTokenId((playerId*100) + count);
		tokens[count].setTokenColor(playerColor);
	}
}

Token *Player::getTokens() {
	return tokens;
}

class Dice {
	NUMBER numberOnDice;
};

class Game {
	int rowCount;
	int colCount;
	int numberOfPlayers;
	Player *players;
	stack<Token *> *board;
	Dice diceOfGame;
	
	public:
	Game();
	void initializeObstacles();
	void setNumberOfPlayers(int);
	int getNumberOfPlayers();
	int getRowCount();
	int getColumnCount();
	Player *getPlayers();
	stack<Token *> *getBoard();
};

Game::Game() {
	rowCount = 6;
	colCount = 9;
	board = new stack<Token *>[rowCount*colCount];
};

void Game::initializeObstacles() {
	srand(time(NULL));
	
	for (int row=0; row < rowCount; row++) {
		int randNum = rand() % 8;
		cout<<(randNum + 1)<<"\n"; // to be removed
		
		int positionOnBoard = (randNum + 1);
		Token *token = new Token();
		token->setTokenId(7*100 + row);
		token->setTokenColor(COLOR::BLACK);
		board[(colCount*row) + positionOnBoard].push(token); 
	}
}

void Game::setNumberOfPlayers(int numPlayers) {
	numberOfPlayers = numPlayers;
	players = new Player[numPlayers];
}

int Game::getNumberOfPlayers() {
	return numberOfPlayers;
}

int Game::getRowCount() {
	return rowCount;
}
	
int Game::getColumnCount() {
	return colCount;
}

Player *Game::getPlayers() {
	return players;
}

stack<Token *> *Game::getBoard() {
	return board;
}

string getColorString(COLOR color) {
	string colorStr;
	switch(color) {
		case RED: 
			colorStr = "RED";
			break;
		case BLUE: 
			colorStr = "BLUE";
			break;
		case GREEN:
			colorStr = "GREEN";
			break;
		case YELLOW:
			colorStr = "YELLOW";
			break;
		case PINK:
			colorStr = "PINK";
			break;
		case ORANGE:
			colorStr = "ORANGE";
			break;
		case BLACK:
			colorStr = "BLACK";
			break;
		default:
			cout<<"Wrong Color Provided\n";
			colorStr = "BLACK";
	}
	return colorStr;
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
					cout<<numberColor<<" ("<<getColorString(it->first)<<") \n";
				}
				numberColor++;
			}
			
			cout<<"\n";
			cin>>chosenNumberColor;
			
			if (chosenNumberColor < 1 || chosenNumberColor > 6) {
				cout<<"Number Chosen is out of Choice\n";
			} else if (remainingColors[numberColors[chosenNumberColor]] == false) {
				cout<<"Color already taken by another player\n";
			} else {
				Player *players = game->getPlayers();
				COLOR color = numberColors[chosenNumberColor];
				
				players[player].setColor(color);
				players[player].setPlayerId(player+1);
				players[player].setTokens();
				
				remainingColors[color] = false;
				colorSelectedByPlayer = true;
			}
		}
	} 
}

void verifyGameParameters(Game *game) {
	cout<<"game info\n";
	cout<<game->getRowCount()<<" "<<game->getColumnCount()<<"\n";
	
	Player *players = game->getPlayers();
	for (int i=0; i < 3; i++) {
		Player p = players[i];
		cout<<getColorString(p.getColor())<<" "<<p.getPlayerId()<<"\n";
		
		Token *t = p.getTokens();
		for (int i=0; i < 4; i++) {
			cout<<t[i].getTokenId()<<" "<<getColorString(t[i].getTokenColor())<<"\n";
		}
	}
	
	// check game board
	stack<Token *> *bd = game->getBoard();
	for (int i=0; i < 54; i++) {
		if (bd[i].empty()) {
			//cout<<"stack empty at "<<i<<"\n";
		} else {
			cout<<"top "<<getColorString((bd[i].top())->getTokenColor())<<" index: "<<i<<"\n";
		}
	}
}

bool checkIdenticalTop(stack<Token *> *board, Player player, int colCount, int row) {
	stack<Token *> stackRow = board[colCount*row];
	cout<<"hh "<<colCount*row<<" "<<getColorString(player.getColor())<<"\n";
	
	if (stackRow.empty())
	return false;
	
	cout<<"top "<<stackRow.top()<<"\n";
	if ((stackRow.top())->getTokenColor() == player.getColor())
	return true;
	
	return false;
}

bool existSmallerStack() {
	return false;
}

void moveAllToLeftColumn(Game *game) {
	cout<<"Starting the Game\n";
	cout<<"We require to place all our tokens on first column of the board\n";
	cout<<"RULE:\n";
	cout<<"A token should be placed first on top of one of the smallest stacks.\n";
	cout<<"A player cannot stack a token on top of his/her token.\n";
	
	int playersCount = game->getNumberOfPlayers();
	int tokensCount = 4;
	int totalMoves = playersCount * tokensCount;
	
	stack<Token *> *board = game->getBoard();
	Player *players = game->getPlayers();
	
	for (int move=0; move < totalMoves; ++move) {
		bool rowSelected = false;
		int row;
		
		cout<<"Player turn: "<<(move%playersCount + 1)<<"\n";
		
		while(!rowSelected) {
			cout<<"Enter the row (1-6) you want to place your token\n";
			cin>>row;
			
			Player player = players[move%playersCount];
			
			if (row < 1 || row > 6) {
				cout<<"Value entered is out of scope. Please try again\n";
			} else if (checkIdenticalTop(board, player, game->getColumnCount(), row-1)) {
				cout<<"Can not stack on your token\n ";
			} else if (existSmallerStack()) {
				cout<<"Place your token on smaller stack\n";
			} else {
				board[game->getColumnCount()*(row-1)].push(&player.getTokens()[move/playersCount]); 
				rowSelected = true;
			}
		}
	}
}

void gameStart(Game *game) {
	moveAllToLeftColumn(game);
}

void verifyTokensLeftmostColumn(Game *game) {
	stack<Token *> *board = game->getBoard();
	
	for (int i=0; i < 6; i++) {
		int index = i*9;
		stack<Token *> s = board[index];
		
		cout<<"index "<<index<<"\n";
		while(!s.empty()) {
			cout<<getColorString((s.top())->getTokenColor())<<"\n";
			cout<<(s.top())->getTokenId()<<"\n";
			s.pop();
		}
	}
}

int main() {
	// Game Initialization
	Game *game = new Game();
	game->initializeObstacles();
	
	// Player Initialization
	initializePlayers(game);
	
	// temporary
	//verifyGameParameters(game);
	
	gameStart(game);
	
	// temporary
	//verifyTokensLeftmostColumn(game);
	
	return 0;
}
