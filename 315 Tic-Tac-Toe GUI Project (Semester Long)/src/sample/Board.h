//board.h

#include <vector>
#include <ncurses.h>

class Board {
    public:
        //squares will contain 'X', 'O', or ' ' (blank space)
        //squares will be of size 64
        std::vector<std::vector<std::vector<char>>> squares;

        //constructors
        Board();
        Board(std::vector<std::vector<std::vector<char>>> _squares);

        //member functions
        void display_board(WINDOW* win);
        void display_numbered_board(WINDOW* win);
        void refresh_squares(WINDOW* win);
        void update(std::vector<std::vector<std::vector<char>>> _squares);
        void update(std::vector<int> square_point, char symbol);
};