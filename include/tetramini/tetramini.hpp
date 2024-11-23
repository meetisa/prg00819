#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP

#include <ncurses.h>
#include "../states/world.hpp"

class Tetramino {
	protected:
		int SCRW;
		int SCRH;
		int XOFF;

		int WIDTH;
		int HEIGHT;

		int STARTX=20;
		int STARTY=1;

		int x;
		int y;

		WINDOW *base;
	public:
		//constructor
		Tetramino(World world, int w, int h);

		void print(int shape);
		virtual void print_frame()=0;

		void move(int dir);
		virtual void safe_move(int dir)=0;

		int falling();
		void dies();

		void getclout(int row, char *buffer);

		virtual void rotate()=0;
		int check_collision();
};

#endif
