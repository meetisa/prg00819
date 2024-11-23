#ifndef GAMEPLAY
#define GAMEPLAY

#include <ncurses.h>
#include "world.hpp"
#include "state.hpp"
#include "../tetramini/tetramini.hpp"
#include "../tetramini/hero.hpp"
#include "../tetramini/smashboy.hpp"

class Partita : public State {
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
