
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Board.h"
#include "highscoreNode.h"
#include "Computer.h"
#include "MinimaxTree.h"
#include "Node.h"

using namespace std;

void print_scores(WINDOW* win, int score_line, vector<string> initials, vector<int> scores) {
	mvwprintw(win, score_line, 0, "HIGH SCORES:\n\n");
	score_line++;
	for (unsigned int i = 0; i < initials.size(); ++i) {
		mvwprintw(win, score_line, 0, (initials.at(i) + "   " + to_string(scores.at(i))).c_str());
		score_line++;
	}
	wrefresh(win);
}

vector<int> indexToPoint(int index) {
	vector<int> v;
	int z = index / 16;
	index = index % 16;
	int y = index / 4;
	index = index % 4;
	int x = index;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);

	return v;
}

//returns position of square on screen
vector<int> pointToLocation(vector<int> point) {
	int row = 2;
	int column = 2;
	if (point[2] == 1) column = 17;
	else if	(point[2] == 2) column = 32;
	else if (point[2] == 3) column = 47;
	
	row += point[1]*2;
	column += point[0]*3;
	vector<int> v = {row, column};
	return v;
}

//checks if the move made at index is a winning move, if so, passes
//vector of the winning indices, if not, vector of size 1
vector<vector<int>> checkWin(vector<vector<vector<char>>> board, int index) {
	if (index < 0 || index > 63) {
		return { { } };
	}

	vector<int> point = indexToPoint(index);
	int x = point[0];
	int y = point[1];
	int z = point[2];
	char piece = board[x][y][z];
	if (piece == ' ') return { { } };

	int matches = 0;
	vector<vector<int>> v;
	//check row
	for (int i = 0; i < 4; i++) {
		if (board[i][y][z] == piece) matches++;
		if (matches == 4) {
			//return indices of entire row
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { j, y, z };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	//check column
	for (int i = 0; i < 4; i++) {
		if (board[x][i][z] == piece) matches++;
		if (matches == 4) {
			//return indices of entire column
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { x, j, z };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	//check down z
	for (int i = 0; i < 4; i++) {
		if (board[x][y][i] == piece) matches++;
		if (matches == 4) {
			//return indices of entire z
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { x, y, j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	//Check XY Diagonals
	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][i][z] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { j, j, z };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][3 - i][z] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { j, 3 - j, z };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	//Check XZ Diagonals
	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][y][i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { j, y, j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][y][3 - i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { j, y, 3 - j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	//Check YZ Diagonals
	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[x][i][i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { x, j, j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[x][i][3 - i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { x, j, 3 - j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	//Check True Diagonals
	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][i][i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { j, j, j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[3 - i][i][i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { 3 - j, j, j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][3 - i][i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { j, 3 - j, j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	matches = 0;
	for (int i = 0; i < 4; i++) {
		if (board[3 - i][3 - i][i] == piece) matches++;
		if (matches == 4) {
			//return indices
			for (int j = 0; j < 4; j++) {
				vector<int> winningPoint = { 3 - j, 3 - j, j };
				v.push_back(winningPoint);
			}
			return v;
		}
	}

	return { { } };
}


int main() {
	int ch;

	WINDOW* win;
	initscr();			// Start curses mode
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	raw();				// Line buffering disabled
	keypad(stdscr, TRUE);
	noecho();
	
	refresh();
	win = newwin(40, 80, 0, 0);

	bool playAgain = true;
	while (playAgain) {
		wclear(win);
		//FIXME: Could redo by reading from .txt file
		wprintw(win, "\n");
		wprintw(win, "   _________  ___   ___    ________   ______    ______\n");
		wprintw(win, "  /________/\\/__/\\ /__/\\  /_______/\\ /_____/\\  /_____/\\\n");
		wprintw(win, "  \\__.::.__\\/\\::\\ \\\\  \\ \\ \\__.::._\\/ \\:::__\\/  \\:::__\\/\n");
		wprintw(win, "     \\::\\ \\   \\::\\/_\\ .\\ \\   \\::\\ \\   \\:\\ \\  __ \\:\\ \\  __ \n");
		wprintw(win, "      \\::\\ \\   \\:: ___::\\ \\  _\\::\\ \\__ \\:\\ \\/_/\\ \\:\\ \\/_/\\\n");
		wprintw(win, "       \\::\\ \\   \\: \\ \\\\::\\ \\/__\\::\\__/\\ \\:\\_\\ \\ \\ \\:\\_\\ \\ \\\n");
		wprintw(win, "        \\__\\/    \\__\\/ \\::\\/\\________\\/  \\_____\\/  \\_____\\/\n");

		wprintw(win, "   _________  ________    ______\n");
		wprintw(win, "  /________/\\/_______/\\  /_____/\\\n");
		wprintw(win, "  \\__.::.__\\/\\::: _  \\ \\ \\:::__\\/\n");
		wprintw(win, "     \\::\\ \\   \\::(_)  \\ \\ \\:\\ \\\n");
		wprintw(win, "      \\::\\ \\   \\:: __  \\ \\ \\:\\ \\/_/\\\n");
		wprintw(win, "       \\::\\ \\   \\:.\\ \\  \\ \\ \\:\\_\\ \\ \\\n");
		wprintw(win, "        \\__\\/    \\__\\/\\__\\/  \\_____\\/\n");

		wprintw(win, "   _________  ______   ______\n");
		wprintw(win, "  /________/\\/_____/\\ /_____/\\\n");
		wprintw(win, "  \\__.::.__\\/\\:::_ \\ \\\\::::_\\/_\n");
		wprintw(win, "     \\::\\ \\   \\:\\ \\ \\ \\\\:\\/___/\\\n");
		wprintw(win, "      \\::\\ \\   \\:\\ \\ \\ \\\\::___\\/_\n");
		wprintw(win, "       \\::\\ \\   \\:\\_\\ \\ \\\\:\\____/\\\n");
		wprintw(win, "        \\__\\/    \\_____\\/ \\_____\\/ \n");

		mvwprintw(win, 11, 48, "TEAM 9");
		mvwprintw(win, 13, 48, "Team Members:");
		mvwprintw(win, 14, 52, "Alex Davis");
		mvwprintw(win, 15, 52, "Kyle Henry");
		mvwprintw(win, 16, 52, "Salman Mithani");

		vector<string> initials;
		vector<int> scores;

		//read in scores from file
		fstream file;
		file.open("scores.txt");
		string line;
		string initial;
		int score;
		
		while (getline(file, line)) {
			if (line.size() < 4) continue;
			initial = line.substr(0, 2);
			score = stoi(line.substr(3));
			initials.push_back(initial);
			scores.push_back(score);
		}

		//print scores below splash screen
		print_scores(win, 24, initials, scores);

		//Blink "start"
		wattron(win, A_BLINK | A_STANDOUT);
		mvwprintw(win, 20, 48, "Press ENTER to start");
		wattroff(win, A_STANDOUT | A_BLINK);

		wrefresh(win);

		ch = getch();

		while (ch != 10) { //ENTER Key pressed
			ch = getch();
		}

		//clear splash screen for board
		wclear(win);

		//ask user for initials and piece
		string user_initials;
		char playerPiece = 'X';
		echo();
		do {
			wprintw(win, "How to Play:\n1. The four grids represent a 3D Tic Tac Toe board.\n");
			wprintw(win, "   The leftmost board is the top plane and the rightmost is the bottom plane\n");
			wprintw(win, "2. Use arrow keys to navigate the grid\n");
			wprintw(win, "3. Press enter to place an 'X' at that position\n");
			wprintw(win, "4. First to four in a row (rows/columns/diagonals) is the winner!\n");
			wprintw(win, "5. Choose either 'X' or 'O' (X goes first)\n\n");
			wprintw(win, "Please enter your initials (two letters): ");
			wrefresh(win);
			char str[10];
			wgetstr(win, str);
			user_initials = str;
			wrefresh(win);
			
			wprintw(win, "\n");
			wprintw(win, "Choose your Piece ('X' or 'O'): ");
			wrefresh(win);
			char str2[2];
			wgetstr(win, str2);
			playerPiece = str2[0];
			wrefresh(win);
		} while (user_initials.size() != 2);
		noecho();
		wclear(win);

		//check if user's initials are already in high scores
		int user_score_index = 0;
		bool user_found = false;
		for (unsigned int i = 0; i < initials.size(); ++i) {
			if (initials.at(i) == user_initials) {
				user_found = true;
				user_score_index = i;
				break;
			}
		}
		
		if(user_found == false) {
			initials.push_back(user_initials);
			scores.push_back(0);
			user_score_index = scores.size()-1;
		}
		
		//Create empty board and display it
		Board board;
		board.display_board(win);
		board.refresh_squares(win);
		//print scores below board
		print_scores(win, 15, initials, scores);
		
		//if user has high score, print it, otherwise put user score on bottom as 0
		if (user_found) {
			mvwprintw(win, 15, 20, ("Your high score: " + to_string(scores.at(user_score_index))).c_str());
		}
		wrefresh(win);

		char computerPiece = playerPiece == 'X' ? 'O' : 'X';
		Computer comp = Computer(computerPiece, board.squares);

		//keeps track of used positions
		vector<int> usedPos;
		
		//Computer moves first if 'X'
		if (computerPiece == 'X') {
			int computerIndex = comp.computerMove();
			vector<int> computerMove = indexToPoint(computerIndex);
			board.update(computerMove, computerPiece);
			board.refresh_squares(win);
			usedPos.push_back(computerIndex);
		}
	
		vector<vector<int>> winningMove;
		if (computerPiece != 'X') board.refresh_squares(win);
		

		while (winningMove.size() != 4) {
			//initialize highlighted box
			int highlightIndex = 0;
			vector<int> highlightPoint = indexToPoint(highlightIndex);
			vector<int> prev_highlightPoint = highlightPoint;
			vector<int> highlightPixel = pointToLocation(highlightPoint);
			vector<int> prev_highlightPixel = highlightPixel;
			mvwchgat(win, highlightPixel.at(0), highlightPixel.at(1), 1, A_NORMAL, 0, NULL);
			wrefresh(win);

			ch = 0;
			//take user input from board
			while ((ch = getch()) != 10) { //wait until user pressed enter on selected square
				switch (ch) {
				case KEY_UP:
					if (highlightPoint.at(1) > 0) {
						highlightIndex = highlightIndex - 4;
					}
					break;
				case KEY_DOWN:
					if (highlightPoint.at(1) < 3) {
						highlightIndex = highlightIndex + 4;
					}
					break;
				case KEY_LEFT:
					if ((highlightPoint.at(0) > 0) || (highlightPoint.at(2) > 0)) {
						if ((highlightPoint.at(2) > 0) && (highlightPoint.at(0) == 0)) {
							highlightIndex = highlightIndex - 13; //swap between board levels
						}
						else {
							highlightIndex = highlightIndex - 1;
						}
					}
					break;
				case KEY_RIGHT:
					if ((highlightPoint.at(0) < 3) || (highlightPoint.at(2) !=3)) {
						if ((highlightPoint.at(2) < 3) && (highlightPoint.at(0) == 3)) {
							highlightIndex = highlightIndex + 13; //swap between board levels
						}
						else {
							highlightIndex = highlightIndex + 1;
						}
					}
					break;
				default:
					break;
				}
				
				highlightPoint = indexToPoint(highlightIndex);
				highlightPixel = pointToLocation(highlightPoint);
				mvwchgat(win, prev_highlightPixel.at(0), prev_highlightPixel.at(1), 1, A_NORMAL, 0, NULL);
				mvwchgat(win, highlightPixel.at(0), highlightPixel.at(1), 1, A_BLINK, 0, NULL);
				prev_highlightPoint = highlightPoint;
				prev_highlightPixel = pointToLocation(prev_highlightPoint);
				wrefresh(win);
			}
			
			//makes sure player did not attempt to play in an occupied location
			bool isUsed = false;
			for (unsigned int i = 0; i < usedPos.size(); ++i) {
				if (highlightIndex == usedPos.at(i)) {
					isUsed = true;
					wattron(win, A_STANDOUT | COLOR_PAIR(1));
					mvwprintw(win, 12, 0, "ERROR: Invalid Move");
					wattroff(win, A_STANDOUT | COLOR_PAIR(1));
					break;
				}
			}

			if (!isUsed) {
				//Display to User was legal move
				mvwprintw(win, 12, 0, "                    "); //clear the old error if exists
				wattron(win, A_STANDOUT | COLOR_PAIR(2));
				mvwprintw(win, 12, 0, "Valid Move");
				wattroff(win, A_STANDOUT | COLOR_PAIR(2));
				
				//Player Move
				vector<int> playerMove = indexToPoint(highlightIndex);
				board.update(playerMove, playerPiece);
				board.refresh_squares(win);
				usedPos.push_back(highlightIndex);

				winningMove = checkWin(board.squares, highlightIndex);
				if (winningMove.size() == 4) break;

				//Computer Move
				comp.update(playerMove);
				int computerIndex = comp.computerMove();
				vector<int> computerMove = indexToPointindexToPoint(computerIndex);
				//string s = to_string(computerMove[0]) + " " + to_string(computerMove[1]) + " " + to_string(computerMove[2]);
				//mvwprintw(win, 20, 0, s.c_str()); //debug computer move
				board.update(computerMove, computerPiece);
				board.refresh_squares(win);
				usedPos.push_back(computerIndex);

				winningMove = checkWin(board.squares, computerIndex);
			}
		}
		
		
		//Determine if someone has won
		if (winningMove.size() == 4) {
			char winningPiece = board.squares[winningMove[0][0]][winningMove[0][1]][winningMove[0][2]];
			
			//Flash red winning squares
			wattron(win, COLOR_PAIR(1) | A_BLINK | A_STANDOUT);
			
			for (int i = 0; i < 4; i++) {
				vector<int> loc = pointToLocation(winningMove[i]);
				mvwprintw(win, loc[0], loc[1], &winningPiece);
				wrefresh(win);
			}
			
			wattroff(win, COLOR_PAIR(1) | A_BLINK | A_STANDOUT);
			
			getch();
			//game is over
			if (winningPiece == playerPiece) {
				playAgain = GameOver(win, 1, user_initials, scores.at(user_score_index));
			}
			else {
				playAgain = GameOver(win, 0, user_initials, scores.at(user_score_index));
			}
		}
		else {
			wclear(win);
			mvwprintw(win, 20, 34, "Cat's Game");
			playAgain = GameOver(win, 0, user_initials, scores.at(user_score_index));
		}
	}
	
	wclear(win);
	wprintw(win, "Player did not want to play again.");
	wrefresh(win);
	getch();
	endwin();
	return 0;
}