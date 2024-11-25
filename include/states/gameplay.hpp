#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include <ctime>
#include <ncurses.h>
#include "world.hpp"
#include "../state_machine/abstract_state.hpp"
#include "../tetramini/tetramini.hpp"
#include "../tetramini/hero.hpp"
#include "../tetramini/smashboy.hpp"

class Partita : public State {
	private:
		World *world;

		double timer;
		clock_t tm;
		double velocity;

		int tick;

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
		int game_over = 1;
		int falls;

	public:
		Partita();

		int update(int input);

		int gameplay(int input);
		void gameOver(int input, char *name, int *points);
};

#endif
