#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP

#include <ncurses.h>
#include "world.hpp"

class Tetramino {
	protected:
		int SCRW;
		int SCRH;
		int XOFF;

		int WIDTH;
		int HEIGHT;

		int STARTX = 5;
		int STARTY = 2;

		int x = STARTX;
		int y = STARTY;

		WINDOW *base;
	public:
		//constructor
		Tetramino(World world, int w, int h);

		void print(int shape);

		void move(int dir);
		int falling();
		void dies();

		void getcoords(int *wx, int *wy);
		void getspecs(int *width, int *height);
		void getclout(int row, char *buffer);
		int check_collision();
		void del();
};

#endif
