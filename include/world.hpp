#ifndef GRID_HPP
#define GRID_HPP

#include <ncurses.h>

typedef struct node {
	node *next;
	int val;
} block;

class World {
	private:
		int SCRW;
		int SCRH;
		int XOFF;
		WINDOW *screen;

		int GRIDW;
		int GRIDH;
		int LEN;

		block *grid = NULL;
		//int *grid;

	public:
		World(int w, int h, int xoff);

		void getspecs(int *w,  int *h, int *xoff);
		int coords_to_pos(int x, int y);
		void pos_to_coords(int pos, int *x, int *y);

		void draw();
		void update_screen();

		//void suckup(Hero t);
		void decompose_block(int x, int y);

		void checkfullrow();
};

#endif
