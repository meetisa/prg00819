#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include "tetramini.hpp"
#include "world.hpp"

#define FRLEN 2

class Hero: public Tetramino {
	protected:
		long int frames[FRLEN] = {
			61440, 8738
			//4369, 8738, 17476, 34952,
			//15, 240, 3840, 61440
		};
		int current=0;
	public:
		Hero(World world);
		void print();
		void move(int dir);
		void rotate();
		int side_collisions();
};

#endif
