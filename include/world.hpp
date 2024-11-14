#ifndef GRID_HPP
#define GRID_HPP

#include <ncurses.h>

typedef struct node {
	node *next;
	int val;
	int row_blocks;
} block;

class World {
	private:
		int SCRW;
		int SCRH;
		int XOFF;
		WINDOW *screen;

		int GRID_XOFF=1;
		int GRID_YOFF=1;

		int GRIDW;
		int GRIDH;
		int LEN;

		block *grid = NULL;

	public:
		World(int w, int h, int xoff);

		void getspecs(int *w,  int *h, int *xoff);
		int coords_to_pos(int x, int y);
		void pos_to_coords(int pos, int *x, int *y);

		void scan();
		void draw();
		void update_screen();

		int checkfullrow();
};

#endif
