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
		WINDOW *org = new WINDOW;
	public:

		Tetramino(int w, int h);

		void update();
		void print(int shape);
		void move(int dir);
		void gravity();
		void getcoords(int *wx, int *wy) {
			*wx = x;
			*wy = y;
		}

		void getclout() {
			char buffer[WIDTH+1];
			for(int i=0; i<WIDTH+1; i++)
				buffer[i] = mvinch(3, i) & A_CHARTEXT;
			buffer[WIDTH] = '\0';

			mvprintw(LINES/2, 5, "%s", buffer);
		}

		int check() {
			return y;
		}
};

#endif
