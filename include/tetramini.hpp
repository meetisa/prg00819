#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP

#include <ncurses.h>

class Tetramino {
	protected:
		int WIDTH;
		int HEIGHT;

		int x=1;
		int y=2;

		WINDOW *base;
		WINDOW *org = new WINDOW;
	public:

		Tetramino(int w, int h);

		void update();
		void print(int shape);
		void move(int dir);
		void gravity();
		void getcoords(int *wx, int *wy);
		void getclout(int row, char *buffer);
		bool check_collision();

		void del();
};

#endif
