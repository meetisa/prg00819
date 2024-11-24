#include "classifica.hpp"

Classifica::Classifica() : State() {
	ifile.open(filename);
	char ch;
	int maxw, maxh;

	while(!ifile.eof()) {
		ifile.get(ch);
		length += ch == '\n';
	}

	length--;

	ifile.close();

	WIDTH = 50;
	/*
	 * il +1 serve per avere una riga vuota
	 * all'inizio e una alla fine (*2 +1),
	 * mentre il +2 sono i bordi sopra e sotto
	 */
	HEIGHT = length * ROW_SPACING +1 +2;

	getmaxyx(stdscr, maxh, maxw);
	STARTY = (maxh/2) - (HEIGHT/2);
	STARTX = (maxw/2) - (WIDTH/2);

	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
}

void Classifica::display() {
	ifile.open(filename);
	char ch;

	int x=0, y=0;

	while(!ifile.eof()) {
		ifile.get(ch);

		if(ch == '\n') {
			y++;
			x = 0;
		}
		else
			mvwprintw(win, TEXT_YOFF + y*2, TEXT_XOFF + x++, "%c", ch);
	}

	ifile.close();

	wrefresh(win);
}
