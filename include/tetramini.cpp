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

void Tetramino::getcoords(int *wx, int *wy) {
	*wx = x;
	*wy = y;
}

bool Tetramino::check_collision() {
	int x, y;
	getcoords(&x, &y);

	char b[WIDTH+1];
	getclout(HEIGHT-1,b);

	const int len=40;
	char row_1[WIDTH];
	for(int i=0; i<WIDTH; i++)
		row_1[i] = mvinch(y+HEIGHT, x+i) & A_CHARTEXT;
	row_1[WIDTH-1] = '\0';

	for(int i=0; i<WIDTH; i=i+2)
		if(b[i] == '[')
			return row_1[i] == '[';
}

void Tetramino::getclout(int row, char *buffer) {
	for(int i=0; i<WIDTH+1; i++)
		buffer[i] = mvwinch(base, row, i) & A_CHARTEXT;
	buffer[WIDTH] = '\0';
}

void Tetramino::del() {
	x = 2;
	y = 2;
}
