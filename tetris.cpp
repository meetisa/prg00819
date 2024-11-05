#include <iostream>
#include <ctime>
#include <ncurses.h>
#include "include/tetramini.hpp"
#include "include/gameplay.hpp"

#define CLOCK 1000000

using namespace std;

int main(int argc, char *argv[]) {

	srand(time(NULL));

	//initialization functions
	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	curs_set(0); //invisible cursor

	gameplay();

	endwin();

	return 0;
}
