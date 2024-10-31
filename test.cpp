#include <iostream>
#include <ctime>
#include <ncurses.h>

#define CLOCK 1000000

using namespace std;

int main(int argc, char *argv[]) {

	//initialization functions
	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	curs_set(0); //invisible cursor

	int tm=0;
	int ch;
	bool done = false;

	int w=40;

	//WINDOW *scr;
	//scr = newwin(LINES, w, 0, 0);
	//box(scr, 0, 0);
	//refresh();
	//wrefresh(scr);

	mvprintw(LINES-1, 0, "ciao");

	int row = LINES-1;
	const int l = COLS/2;
	char buffer[l];
	for(int i=0; i<l; ++i)
		buffer[i] = mvinch(row, i) & A_CHARTEXT;
	buffer[l-1] = '\0';


	mvprintw(1, 0, "%s", buffer);
	while(!done) {
		ch = getch();
		switch(ch) {
			case 'e':
				done = true;
				break;
		}
		refresh();
	}

	endwin();

	return 0;
}
