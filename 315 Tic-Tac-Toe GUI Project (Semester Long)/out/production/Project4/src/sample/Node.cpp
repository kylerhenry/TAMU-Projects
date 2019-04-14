//Node.cpp

#include "Node.h"

using namespace std;

//create node (parent pointer, node's piece, computer piece, board, move)
Node::Node(Node* p, char p2, char cPiece, vector<vector<vector<char>>> b, vector<int> m) {
	parent = p;
	piece = p2;
	board = b;
	lastMove = m;
	computerPiece = cPiece;
	children = vector<Node*>();
	board[m[0]][m[1]][m[2]] = piece;
	value = score(board);
}

//destructor to clean up
Node::~Node() {
	for (auto child : children) {
		delete child;
	}
}

Node* Node::getParent() {
	return parent;
}

int Node::getValue() {
	return value;
}

void Node::setValue(int val) {
	value = val;
}

vector<int> Node::getMove() {
	return lastMove;
}

vector<vector<vector<char>>> Node::getBoard() {
	return board;
}

std::vector<Node*> Node::getChildren() {
	return children;
}

void Node::removeChild(int index) {
	children.erase(children.begin() + index);
}

void Node::insertChild(Node* c) {
	children.push_back(c);
}

//calculates the score of the board of the Node for the computer
int Node::score(vector<vector<vector<char>>> board) {
	//Store number of rows/columns/diagonals with number of X or O at index in appropriate vector
	vector<int> Xs = vector<int>(5);
	vector<int> Os = vector<int>(5);

	//Check all Rows
	for (int k = 0; k < 4; k++) {
		for (int j = 0; j < 4; j++) {
			int numX = 0;
			int numO = 0;
			for (int i = 0; i < 4; i++) {
				if (board[i][j][k] == 'X') numX++;
				else if (board[i][j][k] == 'O') numO++;
			}

			//only increment vector if none of other piece
			if (numO == 0) Xs[numX]++;
			else if (numX == 0) Os[numO]++;
		}
	}

	//Check all Columns
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 4; i++) {
			int numX = 0;
			int numO = 0;
			for (int j = 0; j < 4; j++) {
				if (board[i][j][k] == 'X') numX++;
				else if (board[i][j][k] == 'O') numO++;
			}

			//only increment vector if none of other piece
			if (numO == 0) Xs[numX]++;
			else if (numX == 0) Os[numO]++;
		}
	}

	//Check all Z's
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int numX = 0;
			int numO = 0;
			for (int k = 0; k < 4; k++) {
				if (board[i][j][k] == 'X') numX++;
				else if (board[i][j][k] == 'O') numO++;
			}

			//only increment vector if none of other piece
			if (numO == 0) Xs[numX]++;
			else if (numX == 0) Os[numO]++;
		}
	}

	//Check XY Diagonals
	for (int k = 0; k < 4; k++) {
		int numX = 0;
		int numO = 0;
		for (int i = 0; i < 4; i++) {

			if (board[i][i][k] == 'X') numX++;
			else if (board[i][i][k] == 'O') numO++;
		}
		//only increment vector if none of other piece
		if (numO == 0) Xs[numX]++;
		else if (numX == 0) Os[numO]++;

		//check reverse diagonal
		numX = 0;
		numO = 0;
		for (int i = 0; i < 4; i++) {
			if (board[i][3 - i][k] == 'X') numX++;
			else if (board[i][3 - i][k] == 'O') numO++;
		}
		if (numO == 0) Xs[numX]++;
		else if (numX == 0) Os[numO]++;
	}

	//Check XZ Diagonals
	for (int j = 0; j < 4; j++) {

		int numX = 0;
		int numO = 0;
		for (int i = 0; i < 4; i++) {
			if (board[i][j][i] == 'X') numX++;
			else if (board[i][j][i] == 'O') numO++;
		}
		//only increment vector if none of other piece
		 if (numO == 0) Xs[numX]++;
		else if (numX == 0) Os[numO]++;

		//check reverse diagonal
		numX = 0;
		numO = 0;
		for (int i = 0; i < 4; i++) {
			if (board[i][j][3 - i] == 'X') numX++;
			else if (board[i][j][3 - i] == 'O') numO++;
		}
		if (numO == 0) Xs[numX]++;
		else if (numX == 0) Os[numO]++;
	}

	//Check YZ Diagonals
	for (int i = 0; i < 4; i++) {
		int numX = 0;
		int numO = 0;
		for (int j = 0; j < 4; j++) {
			if (board[i][j][j] == 'X') numX++;
			else if (board[i][j][j] == 'O') numO++;
		}
		//only increment vector if none of other piece
		if (numO == 0) Xs[numX]++;
		else if (numX == 0) Os[numO]++;

		//check reverse diagonal
		numX = 0;
		numO = 0;
		for (int j = 0; j < 4; j++) {
			if (board[i][j][3 - j] == 'X') numX++;
			else if (board[i][j][3 - j] == 'O') numO++;
		}
		if (numO == 0) Xs[numX]++;
		else if (numX == 0) Os[numO]++;
	}

	//Check True Diagonals
	int numX = 0;
	int numO = 0;
	for (int i = 0; i < 4; i++) {

		if (board[i][i][i] == 'X') numX++;
		else if (board[i][i][i] == 'O') numO++;
	}
	//only increment vector if none of other piece
	if (numO == 0) Xs[numX]++;
	else if (numX == 0) Os[numO]++;

	//check reverse diagonal
	numX = 0;
	numO = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][i][3 - i] == 'X') numX++;
		else if (board[i][i][3 - i] == 'O') numO++;
	}
	if (numO == 0) Xs[numX]++;
	else if (numX == 0) Os[numO]++;

	//check other diagonal
	numX = 0;
	numO = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][3 - i][i] == 'X') numX++;
		else if (board[i][3 - i][i] == 'O') numO++;
	}
	if (numO == 0) Xs[numX]++;
	else if (numX == 0) Os[numO]++;

	//check other reverse diagonal
	numX = 0;
	numO = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][3 - i][3 - i] == 'X') numX++;
		else if (board[i][3 - i][3 - i] == 'O') numO++;
	}
	if (numO == 0) Xs[numX]++;
	else if (numX == 0) Os[numO]++;

	//depending on computer piece, change formula
	int score = 0;
	if (computerPiece == 'O') {
		score = 1000 * (Xs[4] - Os[4]) + 100 * (Xs[3] - Os[3]) + 10 * (Xs[2] - Os[2]) + (Xs[1] - Os[1]);
	}
	else {
		score = -1000 * (Xs[4] - Os[4]) - 100 * (Xs[3] - Os[3]) - 10 * (Xs[2] - Os[2]) - (Xs[1] - Os[1]);
	}
	return score;
}