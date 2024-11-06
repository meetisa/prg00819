#ifndef GRID_HPP
#define GRID_HPP

#include <ncurses.h>

class World {
	private:
		int SCRW;
		int SCRH;
		int XOFF;
		WINDOW *screen;

		int GRIDW;
		int GRIDH;
		int LEN;

		int *grid;

	public:
		World(int w, int h, int xoff);

		void getspecs(int *w,  int *h, int *xoff);
		int coords_to_pos(int x, int y);
		void pos_to_coords(int pos, int *x, int *y);

		void draw();
		void update_screen();

		//void suckup(Hero t);

		void checkfullrow();
};

#endif
