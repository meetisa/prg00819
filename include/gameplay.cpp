#include <ctime>
#include "tetramini.hpp"
#include "hero.hpp"
#include "gameplay.hpp"

#define CLOCK 1000000

void gameplay() {
	int tm=0;
	int ch;
	bool done = false;

	int w=40;

	WINDOW *scr;
	scr = newwin(LINES, w, 0, 0);
	box(scr, 0, 0);
	refresh();
	wrefresh(scr);


	Hero t;

	while(!done) {

		t.print();

		/*
		if(tm++ % CLOCK == 0) {
			t.clear();
			if(t.y < LINES-5)
				t.y++;
			t.print();
			tm=0;
		}
		*/

		ch = getch();

		switch(ch) {
			case 'e':
				done = true;
				break;
			case 'r':
				t.rotate();
				break;
			case KEY_LEFT:
				t.move(-1);
				break;
			case KEY_RIGHT:
				t.move(1);
		}

		refresh();
	}
}
