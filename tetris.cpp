#include <iostream>
#include <ctime>
#include <string.h>
#include <ncurses.h>
#include "include/tetramini.hpp"
#include "include/gameplay.hpp"

#define CLOCK 1000000

using namespace std;

int main(int argc, char *argv[]) {
	int tm=0;
	bool done = false;
	int stx, sty, w, h;
	int ch;

	//initialization functions
	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	curs_set(0); //invisible cursor

	move(0, COLS/2);
	for(int i=(COLS/2)+1; i<COLS; i++) {
		for(int j=0; j<LINES; j++)
			mvaddch(j, i, '0');
	}

	Tetramino t(0x000f);
	auto bs = Tetramino(0xffff);
	bs.y = 10;
	bs.print();
	t.print();

	int i=0;

	while(!done) {
		if(tm++ == CLOCK) {
			t.clear();
			if(t.y < bs.y-4)
				t.y++;
			t.print();

			tm=0;
		}

		ch = getch();

		switch(ch) {
			case 'e':
				done = true;
				break;
			case KEY_LEFT:
				t.clear();
				t.x--;
				t.print();
				break;
			case KEY_RIGHT:
				t.clear();
				t.x++;
				t.print();
				break;
		}

		refresh();
	}

	/*
	h = 4;
	w = 8;
	stx = 0;
	sty = 2;

	printw("Press e to exit");
	refresh();

	t = init_win(h, w, sty, stx);
	scr = init_win(LINES, COLS/2, 0, COLS/2);

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++)
			if(matr[i][j])
				mvwprintw(t, i, j*2, "[]");
	}

	wrefresh(t);
	getch();

	*/

	endwin();

	return 0;
}
