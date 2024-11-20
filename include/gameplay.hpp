#ifndef GAMEPLAY
#define GAMEPLAY

#include <ncurses.h>
#include "world.hpp"
#include "tetramini.hpp"
#include "hero.hpp"
#include "smashboy.hpp"

class Partita {
	private:
		World *world;

		/*
		 * si utilizza un puntatore alla classe base
		 * che punterà casualmente, a turno,
		 * una variabile della classe derivata
		 */
		Tetramino *t;
		Hero *h;
		Smashboy *s;

		int input;
		int is_moving=0;
		int points=0;
		int falls;

	public:
		Partita();

		int gameplay(int input, int tick);
};

#endif
