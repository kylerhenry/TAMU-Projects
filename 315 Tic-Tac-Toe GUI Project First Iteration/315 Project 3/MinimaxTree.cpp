//MinimaxTree.cpp

#include "MinimaxTree.h"
#include <vector>
#include <algorithm>

using namespace std;

//Assumes blank board, constructs new MinimaxTree
MinimaxTree::MinimaxTree(vector<vector<vector<char>>> b, char piece) : computerPiece(piece) {
	playerPiece = computerPiece == 'O' ? 'X' : 'O'; //set player piece to other piece

	//Create first layer
	root = new Node(NULL, ' ', computerPiece, b, {0, 0, 0});

	//Create second layer
	for (int k = 0; k < 4; k++) {
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				Node* child = new Node(root, 'X', computerPiece, b, { i, j, k }); //X always moves first
				root->insertChild(child);
			}
		}
	}

	//Create third layer
	for (auto child : root->getChildren()) {
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					//Only make move if blank
					if (child->getBoard()[i][j][k] == ' ') {
						child->insertChild(new Node(child, 'O', computerPiece, child->getBoard(), { i , j, k }));
					}
				}
			}
		}
	}
}

MinimaxTree::~MinimaxTree() {
	delete root;
}

//Returns the next best move by comparing values of nodes in tree
vector<int> MinimaxTree::move() {
	Node* bestMove = root->getChildren()[0];

	//Find move with smallest minimax value
	for (auto child : root->getChildren()) {
		for (auto child2 : child->getChildren()) {
			if (child2->getValue() < bestMove->getValue()) {
				bestMove = child2->getParent();
			}
		}
	}

	return bestMove->getMove();
}

//Traverses down the tree once and creates a new layer
void  MinimaxTree::update(char piece, vector<int> lastMove) {
	Node* lastRoot = root;

	//Set root to child matching last move
	for (unsigned int i = 0; i < root->getChildren().size(); i++) {
		Node* child = root->getChildren()[i];
		if (equal(lastMove.begin(), lastMove.end(), child->getMove().begin())) {
			root = child;
			lastRoot->removeChild(i);
			delete lastRoot; //delete unused paths
			break;
		}
	}

	//Create new layer
	for (auto child : root->getChildren()) {
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					//Only make move if blank
					if (child->getBoard()[i][j][k] == ' ') {
						child->insertChild(new Node(child, piece, computerPiece, child->getBoard(), { i , j, k })); //FIXME: may have to initialize move vector
					}
				}
			}
		}
	}
}