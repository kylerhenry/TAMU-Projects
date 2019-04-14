#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "highscoreNode.h"
#include "printImage.h"

using namespace std;

//when game is won by player or computer, this function is to be called
bool GameOver(WINDOW* win, bool playerWon, string playerInitials, int overallGameScore) {
	wclear(win);

	int newoverallGameScore;
	string imageFileName;
	if (playerWon) {
		//player won the game
		imageFileName = "youwin.txt";
		//adds 1 to user's score
		newoverallGameScore = overallGameScore + 1;
	}
	else {
		//player lost the game
		imageFileName = "youlose.txt";
		newoverallGameScore = overallGameScore;
	}
	//prints you lose/ you win to buffer screen
	printImage(win, imageFileName);

	//inputs current highscores into vector
	string highscoreFileName = "scores.txt";
	ifstream highscoreIn = ifstream(highscoreFileName);
	if (!highscoreIn.is_open()) {
		cerr << "Failed to open highscore input file: " << highscoreFileName << endl;
		exit(1);
	}
	string tempInitial;
	int tempScore;
	vector<highscoreNode> highscores;
	while(!highscoreIn.eof()) {
		highscoreIn >> tempInitial;
		highscoreIn >> tempScore;
		highscoreNode tempHS = { tempInitial, tempScore };
		highscores.push_back(tempHS);
	}
	highscoreIn.close();

	//finds user and updates highscore
	bool newPlayer = true;
	for (unsigned int i = 0; i < highscores.size(); ++i) {
		if (playerInitials == highscores[i].initials) {
			if (highscores[i].highscore < newoverallGameScore) {
				highscores[i].highscore = newoverallGameScore;
			}
			newPlayer = false;
			break;
		}
	}
	//add if new player
	if (newPlayer) {
		highscoreNode player;
		player.initials = playerInitials;
		player.highscore = newoverallGameScore;
		highscores.push_back(player);
	}


	//re-sort highscores
	for(int i = highscores.size() - 1; i > 0; --i) {
		if (highscores[i].highscore > highscores[i - 1].highscore) {
			highscoreNode tempHS = highscores[i - 1];
			highscores[i - 1] = highscores[i];
			highscores[i] = tempHS;
		}
	}

	//makes sure you only store top 5 scores
	while (highscores.size() > 5) {
		highscores.pop_back();
	}

	//write new scores back to disk
	ofstream highscoreOut = ofstream(highscoreFileName, std::ios::out | std::ios::trunc);
	if (!highscoreOut.is_open()) {
		cerr << "Failed to open highscore output file: " << highscoreFileName << endl;
		exit(1);
	}
	for (unsigned int i = 0; i < highscores.size(); ++i) {
		if (i == highscores.size() - 1) {
			highscoreOut << highscores[i].initials << " " << highscores[i].highscore;
		}
		else {
			highscoreOut << highscores[i].initials << " " << highscores[i].highscore << "\n";
		}
	}
	highscoreOut.close();

	//give option to play again or exit
	mvwprintw(win, 20, 20, "Press ENTER to play again, or BACKSPACE to quit.");
	wrefresh(win);
	int ch;
	ch = getch();
	while ((ch != 10) && (ch != 127)) { //wait for ENTER or BACKSPACE Key press
		ch = getch();
	}
	if (ch == 10) {
		return true;
	}
	else if(ch == 127) {
		return false;
	}
}
