#include "classifica.hpp"

// Classifica::Classifica() : State() {
//
// 	player *iter;
// 	iter=head;
//
// 	ifile.open(filename);
// 	char ch, pname[50], points[50];
// 	int maxw, maxh, p, n=0;
// 	int i_n=0, i_p=0;
//
// 	while(!ifile.eof()) {
// 		ifile.get(ch);
//
// 		if(n)
// 			points[i_p++] = ch;
// 		else
// 			pname[i_n++] = ch;
//
// 		if(n && ch == '\n') {
// 			points[i_p] = '\0';
// 			i_p=0;
// 			n = 0;
// 			p = atoi(points);
//
// 			iter->points = p;
//
// 			iter->next = new player;
// 			iter->next->next = NULL;
// 			iter = iter->next;
// 		}
//
// 		if(ch == '@') {
// 			pname[i_n-1] = '\0';
// 			i_n=0;
// 			n=1;
// 			strcpy(iter->name, pname);
// 		}
//
// 		length += ch == '\n';
// 	}
//
// 	length--;
//
// 	ifile.close();
//
// 	WIDTH = 50;
// 	/*
// 	 * il +1 serve per avere una riga vuota
// 	 * all'inizio e una alla fine (*2 +1),
// 	 * mentre il +2 sono i bordi sopra e sotto
// 	 */
// 	HEIGHT = length * ROW_SPACING +1 +2;
//
// 	getmaxyx(stdscr, maxh, maxw);
// 	STARTY = (maxh/2) - (HEIGHT/2);
// 	STARTX = (maxw/2) - (WIDTH/2);
//
// 	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
// }

Classifica::Classifica() : State() {
	int i=0, ch_len=0;
	char ch;
	ifile.open(filename);
	while(!ifile.eof()) {
		ifile.get(ch);
		ch_len++;
	}
	players = new char[ch_len];

	ifile.clear();
	ifile.seekg(0);

	while(!ifile.eof()) {
		ifile.get(players[i++]);
	}
	ifile.close();

	players[ch_len-2] = '\0';

	player *iter;
	iter=head;

	char pname[50], points[50];
	int maxw, maxh, p, n=0;
	int i_n=0, i_p=0;

	for(i=0; i<ch_len; i++) {
		ch = players[i];

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

	chart.init(
		players,
		ROW_SPACING,
		TEXT_XOFF,
		TEXT_YOFF,
		"||--++++"
	);
	chart.setInCenter();
}

void Classifica::display() {
	chart.show_list();
}

int Classifica::update(int input) {
	//if(previous == MENU)
		display();

	return 0;
}

// void Classifica::display() {
// 	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
//
// 	char ch;
// 	int x=0, y=0;
//
// 	ifile.open(filename);
//
// 	while(!ifile.eof()) {
// 		ifile.get(ch);
//
// 		if(ch == '\n') {
// 			y++;
// 			x = 0;
// 		}
// 		else
// 			mvwprintw(win, TEXT_YOFF + y*2, TEXT_XOFF + x++, "%c", ch);
// 	}
//
// 	ifile.close();
//
// 	wrefresh(win);
// }


void Classifica::addPlayer() {
	echo();

	WINDOW *insert_name;
	insert_name = newwin(3, 50, 3, 4);
	wborder(insert_name, '|', '|', '-', '-', '+', '+', '+', '+');

	char name[50];

	mvwscanw(insert_name, 1, 1, "%s", name);

	wrefresh(insert_name);

	noecho();

	char line[100];

	ifile.clear();
	ifile.seekg(0);
	getline(ifile, riga);
}
