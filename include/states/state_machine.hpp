#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <ctime>
#include <ncurses.h>

#include "state.hpp"
#include "menu.hpp"
#include "gameplay.hpp"
#include "classifica.hpp"

class StateMachine {
	private:
		int done = 0;

		state current_state;
		State *states[STATES_LEN];
		State *current;

	public:
		StateMachine(state start);

		void init_ncurses();

		void flip();
		void update(int input);
		void game_loop();
};


#endif
