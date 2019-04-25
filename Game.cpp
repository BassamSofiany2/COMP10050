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

class Game {
	int rowCount;
	int colCount;
	int numberOfPlayers;
	Player *players;
	stack<Token *> *board;
	NUMBER numberOnDice;
	
	public:
	Game();
	void initializeObstacles();
	void setNumberOfPlayers(int);
	int getNumberOfPlayers();
	int getRowCount();
	int getColumnCount();
	Player *getPlayers();
	stack<Token *> *getBoard();
	void setNumberOnDice(int);
	int getNumberOnDice();
};

Game::Game() {
	rowCount = 6;
	colCount = 9;
	board = new stack<Token *>[rowCount*colCount];
};

void Game::initializeObstacles() {
	srand(time(NULL));
	
	for (int row=0; row < rowCount; row++) {
		int randNum = rand() % 7;
		//cout<<(randNum + 1)<<"\n"; 
		
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

void Game::setNumberOnDice(int num) {
	switch (num) {
		case 0:
			numberOnDice = NUMBER::ONE;
			break;
		case 1:
			numberOnDice = NUMBER::TWO;
			break;
		case 2:
			numberOnDice = NUMBER::THREE;
			break;
		case 3:
			numberOnDice = NUMBER::FOUR;
			break;
		case 4:
			numberOnDice = NUMBER::FIVE;
			break;
		case 5:
			numberOnDice = NUMBER::SIX;
			break;
		default:
			numberOnDice = NUMBER::ONE;
	}
}

int Game::getNumberOnDice() {
	int num;
	switch (numberOnDice) {
		case NUMBER::ONE :
			num = 0;
			break;
		case NUMBER::TWO :
			num = 1;
			break;
		case NUMBER::THREE :
			num = 2;
			break;
		case NUMBER::FOUR :
			num = 3;
			break;
		case NUMBER::FIVE :
			num = 4;
			break;
		case NUMBER::SIX :
			num = 5;
			break;
		default:
			num = 0;
	}
	return num;
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
	
	if (stackRow.empty())
	return false;
	
	if ((stackRow.top())->getTokenColor() == player.getColor())
	return true;
	
	return false;
}

bool existSmallerStack(Game *game, int row) {
	stack<Token *> *board = game->getBoard();
	int size = board[game->getColumnCount()*(row-1)].size();
	
	for (int r=0; r < game->getRowCount(); ++r) {
		if (board[game->getColumnCount()*(r-1)].size() < size)
		return true;
	}
	
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
			} else if (existSmallerStack(game, row)) {
				cout<<"Place your token on smaller stack\n";
			} else {
				board[game->getColumnCount()*(row-1)].push(&player.getTokens()[move/playersCount]); 
				rowSelected = true;
			}
		}
	}
}

bool topDoesNotContainPlayerToken(Game *game, int playerTurn, int row) {
	
	stack<Token *> *board = game->getBoard();
	Player *players = game->getPlayers();
	
	if (board[row].empty()) {
		return true;
	}
	
	if( players[playerTurn].getColor() == (board[row].top())->getTokenColor() ) {
		return false;
	}
	
	return true;
}

void moveUpOrDown(Game *game, int playerTurn) {
	int row;
	bool selectionComplete = false;
	
	while(!selectionComplete) {
		cout<<"Enter row from which you want your token to move(1-6)\n";
		cin>>row;
		
		if (row < 1 || row > 6) {
			cout<<"Out of Scope\n";
		} else if (topDoesNotContainPlayerToken(game, playerTurn, (row-1)*game->getColumnCount())) {
			cout<<"Your token is not present in this stack top\n";
		} else {
			char choice;
			cout<<"Do you want to move up or down (u or d) (Input other than u will be considered as d)\n";
			cin>>choice;
			
			stack<Token *> *board = game->getBoard();
			int newRow;
			
			if (choice == 'u') {
				
				if (row == 1) {
					newRow = 6;
				} else {
					newRow = row - 1;
				}
				
				Token *token = board[(row-1)*game->getColumnCount()].top();
				board[(newRow-1)*game->getColumnCount()].push(token);
				board[(row-1)*game->getColumnCount()].pop();
				
			} else {
				
				if (row == 6) {
					newRow = 1;
				} else {
					newRow = row + 1;
				}
				
				Token *token = board[(row-1)*game->getColumnCount()].top();
				board[(newRow-1)*game->getColumnCount()].push(token);
				board[(row-1)*game->getColumnCount()].pop();
			}	
			
			selectionComplete = true;
		}
	}
	
}

void moveToRightStack(Game *game, int row) {
	stack<Token *> *board = game->getBoard();
	
	Token *token = board[row].top();
	board[row+1].push(token);
	board[(row)].pop();
}

bool isCurrentObstacleStack(stack<Token *> *board, int index) {
	if ((board[index].top())->getTokenColor() == COLOR::BLACK)
	return true;
	
	return false;
}

bool matchTokenOnTopObtacleStack(stack<Token *> *board, int index, int playerTurn, Player *players) {
	Token *tokenBlack = board[index].top();
	board[index].pop();
	if (board[index].empty()) {
		board[index].push(tokenBlack);
		return false;
	} else if ((board[index].top())->getTokenColor() == players[playerTurn].getColor()) {
		board[index].push(tokenBlack);
		return true;
	} else {
		board[index].push(tokenBlack);
		return false;
	}
}

int getPlayerTokenIndex(int rowInput, int playerTurn, Game *game) {
	stack<Token *> *board = game->getBoard();
	Player *players = game->getPlayers();
	
	int index = -1;
	
	for (int col=rowInput; col < rowInput + game->getColumnCount(); ++col) {
		if (!board[col].empty()) {
			if (isCurrentObstacleStack(board, col)) {
				if (matchTokenOnTopObtacleStack(board, col, playerTurn, players)) {
					index = col;
					return index;
				}
			} else {
				if ((board[col].top())->getTokenColor() == players[playerTurn].getColor()) {
					index = col; 
					return index;
				}
			}
		}
	}
	
	return -1;
}

bool canTokenMove(stack<Token *> *board, int index, int rowCount, int colCount) {
	for (int row = ((index-1)%colCount); row < rowCount*colCount; row=row+colCount) {
		if (!board[row].empty()) {
			if (isCurrentObstacleStack(board, row) && board[row].size() > 1) {
				return false;
			} else if (!isCurrentObstacleStack(board, row)) {
				return false;
			}
		}
	}
	return true; 
}

bool alreadyOnLastStack(int currentIndex, int num) {
	if (( (currentIndex+1) % num ) != 0)
	return false; 
	
	return true;
}

bool isNextObstacleStack(int index, stack<Token *> *board) {
	
	if (board[index+1].empty())
	return false;
	
	return isCurrentObstacleStack(board, index+1);
}

void moveFromObstacleStack(stack<Token *> *board, int index) {
	Token *tokenBlack = board[index].top();
	board[index].pop();
	
	Token *token = board[index].top();
	board[index].pop();
	
	board[index+1].push(token);
	board[index].push(tokenBlack);
}

void moveToObstacleStack(stack<Token *> *board, int index) {
	Token *token = board[index].top();
	board[index].pop();
	
	Token *tokenBlack = board[index+1].top();
	board[index+1].pop();
	
	board[index+1].push(token);
	board[index+1].push(tokenBlack);
}

void moveToRight(Game *game, int playerTurn, int rowInput) {
	int row;
	row = getPlayerTokenIndex(rowInput, playerTurn, game);
	
	if (row == -1) {
		cout<<"Your token not found in this row (or top of stack)\n";
		return;
	}
	
	stack<Token *> *board = game->getBoard();
	Player *players = game->getPlayers();
	
	if (board[row].empty()) {
		cout<<"No token on this stack \n";
		return;
	}
	
	if (isCurrentObstacleStack(board, row)) {
		
		if (!canTokenMove(board, row, game->getRowCount(), game->getColumnCount())) {
			cout<<"Your token is currently on Obstacle Stack. So you can not move\n";
			return;
		} else {
			cout<<"Your token can move from obstacle stack (since no tokens present on previous column for any row\n";
			moveFromObstacleStack(board, row);
		}
	} else if (alreadyOnLastStack(row, game->getColumnCount())) {
		cout<<"Already on last stack of the row\n";
		return;
	} else if (isNextObstacleStack(row, board)) {
		moveToObstacleStack(board, row); 
	} else {
		moveToRightStack(game, row);
	}
}

void verifyRowTokens(int row, stack<Token *> *board) {
	for (int index=row*9; index < (row*9 + 9); index++) {
		
		stack<Token *> s = board[index];
		
		cout<<"index "<<index<<"\n";
		while(!s.empty()) {
			cout<<getColorString((s.top())->getTokenColor())<<"\n";
			cout<<(s.top())->getTokenId()<<"\n";
			s.pop();
		}
	}
}

void drawUI(Game *game) {
	stack<Token *> *board = game->getBoard();
	int rowCount = game->getRowCount();
	int colCount = game->getColumnCount();
	
	cout<<"Drawing the board.....\n\n";
	
	for (int i=0; i < 48; ++i)
		cout<<"-";
		
	for (int i=0; i < rowCount*colCount; ++i) {
		if (i%colCount == 0)
		cout<<"\n";
		
		for (int j=0; j < 5; ++j) {
			if (j == 0 || j == 4)
			cout<<"|"; 
			else if (j == 3) {
				if (board[i].empty()) {
					cout<<" ";
				} else {
					switch((board[i].top())->getTokenColor()) {
						case COLOR::RED : 
							cout<<"R";
							break;
						case COLOR::BLUE : 
							cout<<"B";
							break;
						case COLOR::GREEN : 
							cout<<"G";
							break;
						case COLOR::YELLOW : 
							cout<<"Y";
							break;
						case COLOR::PINK : 
							cout<<"P";
							break;
						case COLOR::ORANGE : 
							cout<<"O";
							break;
						case COLOR::BLACK : 
							cout<<"K";
							break;
						default:
							cout<<" ";
					}
				}
			} else {
				cout<<" ";
			}
		}
	}
	
	cout<<"\n";
	for (int i=0; i < 48; ++i)
		cout<<"-";
		
	cout<<"Note:\n";
	cout<<"R - RED, B - BLUE, G - GREEN, Y - YELLOW, P - PINK, O - ORANGE, K - Obstacle\n\n";
}

bool checkAnyWinner(Game *game) {
	stack<Token *> *board = game->getBoard();
	Player *players = game->getPlayers();
	int playerCount = game->getNumberOfPlayers();
	
	map<COLOR, int> colorToPlayerMap;
	for(int player = 0; player < playerCount; ++player) {
		colorToPlayerMap[players[player].getColor()] = player;
	}
	
	int countTokenLastStack[playerCount];
	for (int i=0; i < playerCount; ++i) {
		countTokenLastStack[i] = 0;
	}
	
	int colCount = game->getColumnCount();
	int winner = -1;
	for (int row =colCount - 1; row < colCount*(game->getRowCount()); row=row+colCount) {
		stack<Token *> stck = board[row];
		if(!stck.empty()) {
			while (!stck.empty()) {
				Token *token = stck.top();
				stck.pop();
				
				countTokenLastStack[colorToPlayerMap[token->getTokenColor()]]++;
			}
		}
	}
	
	for (int player = 0; player < playerCount; ++player) {
		int winnerTokenCount = 3; 
		if (countTokenLastStack[player] >= winnerTokenCount) {
			winner = player;
			break;
		}
	}
	
	if (winner != -1) {
		cout<<"Player "<<winner<<" wins \n";
		return true;
	}
	
	return false;
} 

void moveLeftToRight(Game *game) {
	bool winnerDecided = false;
	int playersCount = game->getNumberOfPlayers();
	int playerTurn = 0;
	char choice;
	
	cout<<"Now we will start moving towards right \n";
	cout<<"RULE:\n";
	cout<<"Roll the dice\n";
	cout<<"Move your token up or down (Optional)\n";
	cout<<"Move forward one of the token at the row indicated by the dice(Mandatory) \n";
	
	while (!winnerDecided) {
		cout<<"Player turn: "<<(playerTurn + 1)<<"\n";
		cout<<"Rolling the dice.....\n";
		
		int diceNum = 4; //rand() % 6; // temp
		cout<<"Dice number: "<<(diceNum + 1)<<"\n";
		
		game->setNumberOnDice(diceNum);
		
		cout<<"Do you want to move your token up or down (y or n) (Value other than y will be treated as n)\n";
		cin>>choice;
		
		// Any other option will be treated as n.
		if (choice == 'y') {
			moveUpOrDown(game, playerTurn);
		}
		
		cout<<"We will now move to right for row "<<(diceNum + 1)<<"\n";
		moveToRight(game, playerTurn, diceNum*(game->getColumnCount()));
		
		// temp
		//verifyRowTokens(4, game->getBoard());
		
		drawUI(game);
		
		if (checkAnyWinner(game))
		winnerDecided = true;
		
		if (rand() % 20 == 10) // temp
		winnerDecided = true; // temp
		
		playerTurn = ((playerTurn+1)%playersCount);
	}
}

void gameStart(Game *game) {
	moveAllToLeftColumn(game);
	moveLeftToRight(game);
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

void verifyTokensSecondColumn(Game *game) {
	stack<Token *> *board = game->getBoard();
	
	for (int i=0; i < 6; i++) {
		int index = i*9 + 1;
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
	
	//temporary
	verifyTokensSecondColumn(game);
	
	return 0;
	// Improvements: does not handle the case if same token is present in same row such that obstacle stack is behind.
	// saving dice value in game obect but not using
	
}
