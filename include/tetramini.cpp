#include <iostream>
#include "tetramini.hpp"

Tetramino::Tetramino(int w, int h) {
	WIDTH = w*2;
	HEIGHT = h;

	base = newwin(HEIGHT, WIDTH, y, x);
}

void Tetramino::print(int shape) {
	/*
	for(int i=0; i<WIDTH*HEIGHT; i++)
		if(shape[i] == '1')
			mvwprintw(base, i/HEIGHT, (i%HEIGHT)*2, "[]");
	*/

	int c=0;
	for(int i=shape; i!=0; i/=2) {
		if(i % 2)
			mvwprintw(base, c/HEIGHT, (c%HEIGHT)*2, "[]");
		c++;
	}
	wrefresh(base);
	//update();
}

void Tetramino::move(int dir) {
	x += dir;
	mvwin(base, y, x);
	wrefresh(base);
}

void Tetramino::gravity() {
	y += 1;
	mvwin(base, y, x);
	wrefresh(base);
}


