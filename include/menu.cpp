#include "menu.hpp"

Menu::Menu() {
	int maxw, maxh;
	int i;

	getmaxyx(stdscr, maxh, maxw);
	STARTY = (maxh/2) - (HEIGHT/2);
	STARTX = (maxw/2) - (WIDTH/2);

	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

	for(i=0; i<OPT_LEN; i++) {
		mvwprintw(win, (i*2)+2, 4, "%s", options[i]);
	}

	refresh();

	CRS_Y = cursor*2 + 2;
	mvwprintw(win, CRS_Y, CRS_X, "%c", CRS_CH);
}

int Menu::choose(int input) {
	if(input == KEY_DOWN || input == KEY_UP) {
		mvwprintw(win, CRS_Y, CRS_X, " ");

		cursor++;
		if(cursor >= OPT_LEN)
			cursor = 0;

		CRS_Y = cursor*2 + 1 + 1;
		wattron(win, A_BOLD);

		mvwprintw(win, CRS_Y, CRS_X, "%c", CRS_CH);

		wattroff(win, A_BOLD);
	}

	wrefresh(win);

	if(input == ' ')
		return cursor;
	else
		return -1;
}
