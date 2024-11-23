#include "menu.hpp"

Menu::Menu() {
	int maxw, maxh;
	int i;

	WIDTH = 40;
	/*
	 * il +1 serve per avere una riga vuota
	 * all'inizio e una alla fine (*2 +1),
	 * mentre il +2 sono i bordi sopra e sotto
	 */
	HEIGHT = OPT_LEN*ROW_SPACING +1 +2;

	getmaxyx(stdscr, maxh, maxw);
	STARTY = (maxh/2) - (HEIGHT/2);
	STARTX = (maxw/2) - (WIDTH/2);

	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

	for(i=0; i<OPT_LEN; i++) {
		mvwprintw(win, i*ROW_SPACING + TEXT_YOFF, TEXT_XOFF, "%s", options[i]);
	}

	refresh();

	CRS_Y = cursor*ROW_SPACING + CRS_YOFF;
	mvwprintw(win, CRS_Y, CRS_X, "%c", CRS_CH);
}

void Menu::update(int input) {
	if(input == KEY_DOWN || input == KEY_UP) {
		mvwprintw(win, CRS_Y, CRS_X, " ");

		cursor++;
		if(cursor >= OPT_LEN)
			cursor = 0;

		CRS_Y = cursor*ROW_SPACING + CRS_YOFF;
		wattron(win, A_BOLD);

		mvwprintw(win, CRS_Y, CRS_X, "%c", CRS_CH);

		wattroff(win, A_BOLD);
	}

	wrefresh(win);

/*	if(input == ' ')
		return cursor;
	else
		return -1*/;
}
