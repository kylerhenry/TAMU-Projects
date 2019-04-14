//Node.h

#pragma once
#include <vector>


class Node {
private:
	int value;
	Node* parent;
	char piece;
	char computerPiece;
	std::vector<std::vector<std::vector<char>>> board;
	std::vector<int> lastMove;
	std::vector<Node*> children;

public:
	Node(Node* p, char p2, char cPiece, std::vector<std::vector<std::vector<char>>> b, std::vector<int> m);
	~Node();
	Node* getParent();
	int getValue();
	void setValue(int val);
	std::vector<int> getMove();
	std::vector<std::vector<std::vector<char>>> getBoard();
	std::vector<Node*> getChildren();
	void removeChild(int index);
	void insertChild(Node* c);
	int score(std::vector<std::vector<std::vector <char>>> board);
};