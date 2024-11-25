#ifndef ABSTRACT_STATE_MACHINE_HPP
#define ABSTRACT_STATE_MACHINE_HPP

#include <ctime>
#include <ncurses.h>

#include "abstract_state.hpp"

#include "../states/menu.hpp"
#include "../states/gameplay.hpp"
#include "../states/classifica.hpp"

class StateMachine {
	protected:
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
