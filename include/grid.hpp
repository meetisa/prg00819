#ifndef GRID_HPP
#define GRID_HPP

#include <ncurses.h>
#include "tetramini.hpp"
#include "hero.hpp"

class Grid {
	private:
		int len;
		int width, height;
		int *grid;
	public:
		Grid(int w, int h);
		int coords_to_pos(int x, int y);
		void pos_to_coords(int pos, int *x, int *y);
		void draw();
		void suckup(Hero t);
};

#endif
