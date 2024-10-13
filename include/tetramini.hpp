#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP

#include <ncurses.h>

class Tetramino {
	protected:
		int WIDTH;
		int HEIGHT;

		int x=2;
		int y=2;

		WINDOW *base;
	public:

		Tetramino(int w, int h);

		void print(char *shape);
		void move(int dir);
		void rotate(int dir);
};

#endif
