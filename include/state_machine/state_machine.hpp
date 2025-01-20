#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <ctime>
#include <ncurses.h>

#include "state.hpp"

#include "../states/menu.hpp"
#include "../states/gameplay.hpp"
#include "../states/classifica.hpp"

/**
 * Implentazione di una macchina a stati minimalista
 *
 * Controlla gli stati del gioco e ne facilita il cambio
 * al verificarsi di certi eventi.
 * Permette gestire meglio le interazioni tra i vari stati.
 */
class StateMachine {
	protected:
		int done = 0;

		state current_state;
		State *states[STATES_LEN];
		State *current;

	public:
		/// Costruttore della classe
		StateMachine(state start);

		/// Inizializza le funzioni di ncurses
		void init_ncurses();

		/// Cambia stato di gioco
		void flip();

		/// Aggiorna lo stato attuale
		void update(int input);

		/// Ciclo principale del gioco
		void game_loop();
};


#endif
