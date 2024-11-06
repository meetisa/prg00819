#ifndef SMASHBOY_HPP
#define SMASHBOY_HPP

#include "world.hpp"

class Smashboy: public Tetramino {
	protected:
		int frame = 15;
		//char frame[5] = "1111";

	public:
		Smashboy(World world);
		void print();
		void rotate() {}
};

#endif
