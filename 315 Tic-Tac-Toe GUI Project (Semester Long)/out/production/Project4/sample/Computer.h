//Computer.h

#pragma once
#include <vector>
#include "MinimaxTree.h"

class Computer {
private:
	std::vector<std::vector<std::vector<char>>> board;
	MinimaxTree* tree;
	char computerPiece;
	char playerPiece;
public:
	Computer(char piece, std::vector<std::vector<std::vector<char>>> b);
	~Computer();
	int pointToIndex(std::vector<int> v);
	void update(std::vector<int> move);
	int computerMove();
};