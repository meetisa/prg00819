#include <ctime>
#include "tetramini.hpp"
#include "hero.hpp"
#include "smashboy.hpp"
#include "gameplay.hpp"

#define CLOCK 100000

void gameplay() {
	int tm=0;
	int ch;
	bool done = false;

	int w=40;

	WINDOW *scr;
	scr = newwin(LINES, w, 0, 0);
	wborder(scr, '|', '|', '−', '−', '+', '+', '+', '+');
	refresh();
	wrefresh(scr);

	Hero t;
	int wx, wy;
	const int l = COLS/2;
	char buffer[l];

	while(!done) {
		touchwin(scr);
		t.getcoords(&wx, &wy);

		/*
		for(int i=0; i<l; i++)
			buffer[i] = mvwinch(scr, wy, i) & A_CHARTEXT;
		buffer[l-1] = '\0';

		mvprintw(LINES/2, 5, "%s", buffer);
		*/
		t.getclout();
		t.print();

		/*
		if(++tm % CLOCK == 0) {
			if(t.check() < LINES-5)
				t.gravity();
			t.print();
			tm=0;
		}
		*/

		ch = getch();

		switch(ch) {
			case 'e':
				done = true;
				break;
			case 'p':
				chtype* p;
				int n;
				n = inchstr(p);
				mvprintw(0, 0, "%s", n);
				break;
			case 'r':
				t.rotate();
				break;
			case KEY_LEFT:
				if(wx > 1)
					t.move(-1);
				wborder(scr, '|', '|', '−', '−', '+', '+', '+', '+');
				wrefresh(scr);
				break;
			case KEY_RIGHT:
				if(wx <= w-4)
					t.move(1);
				wborder(scr, '|', '|', '−', '−', '+', '+', '+', '+');
				wrefresh(scr);
				break;
		}

		refresh();
	}
}
