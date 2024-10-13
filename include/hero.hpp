#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include "tetramini.hpp"

class Hero: public Tetramino {
	protected:
		char frames[2][17] = {
			"0100010001000100",
			"0000111100000000"
		};
		int current=1;

	public:
		Hero();
		void print();
		void rotate() {
			werase(base);
			wrefresh(base);
			current = current ? 0 : 1;
			print();
		}
};

#endif
