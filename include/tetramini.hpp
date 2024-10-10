#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP

#include <ncurses.h>

#define WIDTH 8
#define HEIGHT 4

class Tetramino {
	public:
		int id;
		int x=0, y=2;
		WINDOW *base;
		Tetramino(int coords);
		void print();
		void clear();
};

#endif
