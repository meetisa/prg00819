#include "classifica.hpp"

Classifica::Classifica() : State() {

	player *iter;
	iter=head;

	ifile.open(filename);
	char ch, pname[50], points[50];
	int maxw, maxh, p, n=0;
	int i_n=0, i_p=0;

	while(!ifile.eof()) {
		ifile.get(ch);

		if(n)
			points[i_p++] = ch;
		else
			pname[i_n++] = ch;

		if(n && ch == '\n') {
			points[i_p] = '\0';
			i_p=0;
			n = 0;
			p = atoi(points);

			iter->points = p;

			iter->next = new player;
			iter->next->next = NULL;
			iter = iter->next;
		}

		if(ch == '@') {
			pname[i_n-1] = '\0';
			i_n=0;
			n=1;
			strcpy(iter->name, pname);
		}

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
}

int Classifica::update(int input) {
	if(previous == MENU)
		display();

	return 0;
}

void Classifica::display() {
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

	char ch;
	int x=0, y=0;

	ifile.open(filename);

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


void Classifica::addPlayer(player p) {
}
