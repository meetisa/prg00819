#include <ctime>
#include "grid.hpp"
#include "tetramini.hpp"
#include "hero.hpp"
#include "smashboy.hpp"
#include "gameplay.hpp"

#define CLOCK 20000
#define WIDTH 40

void updatescr(WINDOW *scr) {
	wborder(scr, '|', '|', '−', '−', '+', '+', '+', '+');
	wrefresh(scr);
}

void gameplay() {
	int tm=0;
	int ch;
	bool done = false;

	WINDOW *scr;
	scr = newwin(LINES, WIDTH, 0, 0);
	refresh();
	updatescr(scr);

	Hero t;

	int wx, wy;
	char buffer[WIDTH+1];

	auto g = Grid(WIDTH, LINES);

	while(!done) {
		t.getcoords(&wx, &wy);

		t.print();
		mvprintw(1, 0, "%d\t%d", wx, wy);
		//t.getclout(3, 9);
		//t.getclout(wy+4, 10);


		if(++tm % CLOCK == 0) {
			if(!t.check_collision() && wy < LINES-5)
				t.gravity();
			else {
				g.suckup(t);
				//t.del();
			}
			t.print();
			tm=0;
			updatescr(scr);
		}

		ch = getch();

		switch(ch) {
			case 'e':
				done = true;
				break;
			case 'p':
				break;
			case 'r':
				t.rotate();
				break;
			case KEY_LEFT:
				if(wx > 1)
					t.move(-2);
				updatescr(scr);
				break;
			case KEY_RIGHT:
				if(wx <= WIDTH-4)
					t.move(2);
				updatescr(scr);
				break;
		}

		g.draw();
		refresh();
	}
}
