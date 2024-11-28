#include "screen.hpp"

/* SCREEN */

void Screen::init(int w, int h, int stx, int sty, char *borders) {
	WIDTH = w;
	HEIGHT = h;

	STARTX = stx;
	STARTY = sty;

	strcpy(BORDERS, borders);

	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
}

void Screen::setInCenter() {
	int maxh, maxw;
	getmaxyx(stdscr, maxh, maxw);

	int middle_y = (maxh/2) - (HEIGHT/2);
	int middle_x = (maxw/2) - (WIDTH/2);

	mvwin(win, middle_y, middle_x);
}

void Screen::show() {
	wborder(
		win,
		BORDERS[0],
		BORDERS[1],
		BORDERS[2],
		BORDERS[3],
		BORDERS[4],
		BORDERS[5],
		BORDERS[6],
		BORDERS[7]
	);

	wrefresh(win);
}

/* LIST */

void List::init(char text[], int r_s, int txt_xoff, int txt_yoff, char borders[]) {
	int i, len=0, tmp;
	int maxw = 0;

	ROW_SPACING = r_s;
	TEXT_XOFF = txt_xoff;
	TEXT_YOFF = txt_yoff;

	TOTAL_CHARS_LEN = strlen(text);
	list = new char[TOTAL_CHARS_LEN];
	strcpy(list, text);

	for(i=0; i<TOTAL_CHARS_LEN; i++) {
		if(list[i] == '\n') {
			LENGTH++;
			if(len > maxw) {
				tmp = len;
				len = maxw;
				maxw = tmp;
			}
			len = 0;
		}
		else
			len++;
	}


	int w = maxw + (TEXT_XOFF*2);

	/*
	 * | bordo sopra (+1)
	 * |--------------
	 * | +TEXT_YOFF sopra
	 * |--------------
	 * | (numero righe * spazio tra esse) - (spazio-1)
	 * |--------------
	 * | +TEXT_YOFF sotto
	 * |--------------
	 * | bordo sotto (+1)
	 */
	int h = (TEXT_YOFF*2) +2 +(LENGTH*ROW_SPACING)-(ROW_SPACING-1);

	Screen::init(w, h, 0, 0, borders);
}

void List::show_list() {

	int i;
	int y=TEXT_YOFF+1, x=TEXT_XOFF;


	for(i=0; i<TOTAL_CHARS_LEN; i++) {
		if(list[i] == '\n') {
			y += ROW_SPACING;
			x = TEXT_XOFF;
		}
		else
			mvwprintw(win, y, x++, "%c", list[i]);
	}

	Screen::show();
}
