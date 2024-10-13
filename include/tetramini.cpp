#include <iostream>
#include "tetramini.hpp"

Tetramino::Tetramino(int w, int h) {
	WIDTH = w*2;
	HEIGHT = h;

	base = newwin(HEIGHT, WIDTH, y, x);
}

void Tetramino::print(char *shape) {
	for(int i=0; i<HEIGHT; i++)
		for(int j=0; j<WIDTH; j++)
			if(shape[(i*WIDTH)+j] == '1')
				mvwprintw(base, i, j*2, "[]");

	wrefresh(base);
}

void Tetramino::move(int dir) {
	x += dir;
	werase(base);
	wrefresh(base);
	mvwin(base, y, x);
}

void Tetramino::rotate(int dir) {

}
