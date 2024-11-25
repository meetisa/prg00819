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

void List::init(int w, int h, int stx, int sty, char borders[]) {
	Screen::init(w, h, stx, sty, borders);
}

void List::init_text(char text[], int l, int r_s, int txt_xoff, int txt_yoff) {
	ROW_SPACING = r_s;
	LENGTH = l;
	TEXT_XOFF = txt_xoff;
	TEXT_YOFF = txt_yoff;

	list = new char[LENGTH];

	int i;
	for(i=0; i<LENGTH; i++)
		strcpy(list, text);
}

void List::show_list() {
	int sl;
	int y=0;
	sl = strlen(list);
	for(int i=0; i<sl; i++) {
		if(list[i] == '\n')
			y++;

		mvwprintw(win, y*ROW_SPACING + TEXT_YOFF, TEXT_XOFF, "%c", list[i]);
	}

	Screen::show();
}
