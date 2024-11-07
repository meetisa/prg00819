#include <ctime>
#include "world.hpp"
#include "tetramini.hpp"
#include "hero.hpp"
#include "smashboy.hpp"
#include "gameplay.hpp"

#define CLOCK 20000
#define SCREEN_WIDTH 40

#define X_OFFSET 2

void gameplay() {
	int tm=0;
	int ch;
	bool done = false;


	int tetr_x, tetr_y;
	int tetr_w, tetr_h;

	refresh();

	auto world = World(SCREEN_WIDTH, LINES, X_OFFSET);
	world.update_screen();

	Hero t(world);

	while(!done) {

		t.getcoords(&tetr_x, &tetr_y);
		t.getspecs(&tetr_w, &tetr_h);
		t.print();

		mvprintw(0, 0, "%d", t.side_collisions());


		if(++tm % CLOCK == 0) {

			if(!t.falling()) {
				//world.suckup(t);
				t.dies();
				//world.checkfullrow();
				t.del();
			}
			tm=0;
			world.update_screen();
		}


		ch = getch();

		if(ch == 'e')
			done = true;
		else if(ch == 'r')
			t.rotate();
		else if(ch == KEY_LEFT || ch == KEY_RIGHT) {
			t.move(2 - 4*(ch == KEY_LEFT));
			world.update_screen();
		}

		world.draw();
		refresh();
	}
}
