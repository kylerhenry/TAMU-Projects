#ifndef HIGHSCORENODE_H
#define HIGHSCORENODE_H

#include <string>

using namespace std;

//defines the "node" data stucture for storing highscores

struct highscoreNode {
	string initials;
	int highscore;
};

bool GameOver(WINDOW* win, bool playerWon, string playerInitials, int overallGameScore);


#endif