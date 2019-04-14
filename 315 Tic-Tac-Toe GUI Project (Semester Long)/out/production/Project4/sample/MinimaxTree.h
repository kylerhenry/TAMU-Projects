//MinimaxTree.h

#pragma once
#include "Node.h"
#include <vector>

class MinimaxTree {
private:
	Node* root;
	char computerPiece;
	char playerPiece;
public:
	MinimaxTree(std::vector<std::vector<std::vector<char>>> b, char piece);
	~MinimaxTree();
	void update(char piece, std::vector<int> lastMove);
	std::vector<int> move();
};