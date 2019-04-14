//board.h

#include "Board.h"
#include <string>
#include <vector>

using namespace std;

//default constructor populates squares with blanks
Board::Board() {
    for(int k = 0; k < 4; ++k) {
		vector<vector<char>> vy;
		for (int j = 0; j < 4; j++) {
			vector<char> vz;
			for (int i = 0; i < 4; i++) {
				vz.push_back(' ');
			}
			vy.push_back(vz);
		}
		squares.push_back(vy);
    }
}

//this constructor accepts pre-populated squares vector
Board::Board(vector<vector<vector<char>>> _squares) {
    squares = _squares;
}

//display blank board
void Board::display_board(WINDOW* win) {
    wprintw(win, "  TOP PLANE                                  BOTTOM PLANE\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wrefresh(win);
}

//display numbered board
//can be used in tutorial if necessary
void Board::display_numbered_board(WINDOW* win) {
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "| 1| 2| 3| 4|  |17|18|19|20|  |33|34|35|36|  |49|50|51|52|\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "| 5| 6| 7| 8|  |21|22|23|24|  |37|38|39|40|  |53|54|55|56|\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "| 9|10|11|12|  |25|26|27|28|  |41|42|43|44|  |57|58|59|60|\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wprintw(win, "|13|14|15|16|  |29|30|31|32|  |45|46|47|48|  |61|62|63|64|\n");
    wprintw(win, "+--+--+--+--+  +--+--+--+--+  +--+--+--+--+  +--+--+--+--+\n");
    wrefresh(win);
}

//helper function to convert character to string
string cToS(char c) {
    string s(1, c);
    return s;
}

//update single square
void Board::update(vector<int> square_point, char symbol) {
    squares[square_point[0]][square_point[1]][square_point[2]] = symbol;
}

//update entire board with squares vector provided to function
void Board::update(std::vector<std::vector<std::vector<char>>> _squares) {
    squares = _squares;
}

//print squares on board
//call this function every time board is updated to reprint
void Board::refresh_squares(WINDOW* win) {
    int line = 2;
    int col = 2;
    int numprinted = 0;

    //print top plane
	for (int j = 0; j < 4; j++) {
		for(int i = 0; i < 4; ++i) {
			mvwprintw(win, line, col, cToS(squares[i][j][0]).c_str());
			numprinted++;
			col += 3;
        }
		line += 2;
		col = 2;
    }

    line = 2;
    col = 17;

    //print 2nd plane
	for (int j = 0; j < 4; j++) {
		for(int i = 0; i < 4; ++i) {
			mvwprintw(win, line, col, cToS(squares[i][j][1]).c_str());
			numprinted++;
			col += 3;
        }
		line += 2;
		col = 17;
    }

    line = 2;
    col = 32;

    //print 3rd plane
	for (int j = 0; j < 4; j++) {
		for(int i = 0; i < 4; ++i) {
			mvwprintw(win, line, col, cToS(squares[i][j][2]).c_str());
			numprinted++;
			col += 3;
		}
		line += 2;
		col = 32;
    }

    line = 2;
    col = 47;

    //print bottom plane
    for(int j = 0; j < 4; ++j) {
		for (int i = 0; i < 4; i++) {
			mvwprintw(win, line, col, cToS(squares[i][j][3]).c_str());
			numprinted++;
			col += 3;
		}
		line += 2;
		col = 47;
    }

    wrefresh(win);
}