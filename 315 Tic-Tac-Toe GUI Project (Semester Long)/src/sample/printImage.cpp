#include <ncurses.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include "printImage.h"
//function for printing ACSII images from file

void printImage(WINDOW* win, string fileName) {
	ifstream imageIn;
	imageIn.open(fileName);
	string imageLine;
	while (getline(imageIn, imageLine)) {
		wprintw(win, "%s \n", imageLine.c_str());
	}
	return;
}