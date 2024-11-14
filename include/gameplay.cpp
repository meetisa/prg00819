#include <ctime>
#include "world.hpp"
#include "tetramini.hpp"
#include "hero.hpp"
#include "smashboy.hpp"
#include "gameplay.hpp"

#define CLOCK 10000
#define SCREEN_WIDTH 42

#define X_OFFSET 2

void gameplay() {

	srand(time(NULL));

	int tm=0;
	int ch;
	bool done = false;

	WINDOW *points_scr;
	points_scr = newwin(3, 25, 2, 50);
	wborder(points_scr, '|', '|', '-', '-', '+', '+', '+', '+');
	int points=0;

	refresh();

	auto world = World(SCREEN_WIDTH, LINES, X_OFFSET);
	world.update_screen();

	Tetramino *t;
	Hero h(world);
	Smashboy s(world);

	if(rand() % 2)
		t = &h;
	else
		t = &s;

	while(!done) {

		wborder(points_scr, '|', '|', '-', '-', '+', '+', '+', '+');
		mvwprintw(points_scr, 1, 1, "punteggio: %d", points);
		wrefresh(points_scr);

		t->print_frame();

		if(++tm % CLOCK == 0) {
			if(!t->falling()) {
				t->dies();
				world.scan();
				points += world.checkfullrow();
				t->del();
				if(rand() % 2) t = &h;
				else t = &s;
			}
			tm=0;
			world.update_screen();
		}

		ch = getch();

		if(ch == 'q')
			done = true;
		else if(ch == 'r')
			t->rotate();
		else if(ch == KEY_LEFT || ch == KEY_RIGHT) {
			t->move(2 - 4*(ch == KEY_LEFT));
			world.update_screen();
		}

		world.draw();
		refresh();
	}
}
