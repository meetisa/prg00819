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
		//dimensioni dello schermo di gioco
		int SCRW, SCRH;

		//differenza di posizione rispetto all'origine
		int XOFF;

		WINDOW *screen;


		//dimesioni dello schermo dei punti
		int PNT_SCRW = 25;
		int PNT_SCRH = 3;

		//posizione dello schermo dei punti
		int PNT_SCRX = 50;
		int PNT_SCRY = 2;

		WINDOW *points_scr;


		/*
		 * differenze di posizione dei blocchi
		 * rispetto allo schermo di gioco
		 */
		int GRID_XOFF=1;
		int GRID_YOFF=1;

		//dimensioni della griglia
		int GRIDW;
		int GRIDH;
		int LEN;

		//la griglia è una lista concatenata
		block *grid;

	public:
		//costruttore
		World(int w, int h, int xoff);

		void getspecs(int *w,  int *h, int *xoff);
		void pos_to_coords(int pos, int *x, int *y);

		void scan();
		void draw();
		void update_screen();
		void update_points(int p);

		int checkfullrow();
};

#endif
