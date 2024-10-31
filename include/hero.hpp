#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include "tetramini.hpp"

#define FRLEN 8

class Hero: public Tetramino {
	protected:
		long int frames[FRLEN] = {
			4369, 8738, 17476, 34952,
			15, 240, 3840, 61440
		};
		int current=0;
	public:
		Hero();
		void print();
		void rotate();
};

#endif
