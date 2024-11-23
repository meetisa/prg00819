#ifndef SMASHBOY_HPP
#define SMASHBOY_HPP

#include "../states/world.hpp"

class Smashboy: public Tetramino {
	protected:
		int frame = 15;
		//char frame[5] = "1111";

	public:
		Smashboy(World world);
		void print_frame();
		void safe_move(int dir);
		void rotate() {}
};

#endif
