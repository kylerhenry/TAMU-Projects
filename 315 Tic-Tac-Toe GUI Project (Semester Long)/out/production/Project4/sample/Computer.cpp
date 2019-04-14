//Computer.cpp

#include <vector>
#include "Computer.h"

using namespace std;

//create new computer(computer piece, board)
Computer::Computer(char piece, std::vector<std::vector<std::vector<char>>> b) : board(b), computerPiece(piece) {
	playerPiece = computerPiece == 'O' ? 'X' : 'O';
	tree = new MinimaxTree(b, piece);
}

//destructor to clean up
Computer::~Computer() {
	delete tree;
}

int Computer::pointToIndex(std::vector<int> v) {
	return v[0] + v[1] * 4 + v[2] * 16;
}

void Computer::update(std::vector<int> move) {
	tree->update(playerPiece, move);
}

//Makes computer move, returns index of computer's move
int Computer::computerMove() {
	vector<int> move = tree->move();
	tree->update(computerPiece, move);
	return pointToIndex(move);
}