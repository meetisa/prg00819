#include <ncurses.h>
#include <iostream>

using namespace std;

int main() {
	initscr();

	int h=10, w=20, x=10, y=10;

	WINDOW * win = newwin(h, w, x, y);
	refresh();

	box(win, 0, 0);
	wrefresh(win);

	getch();
	endwin();

	return 0;
}
