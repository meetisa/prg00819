#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include <ctime>
#include <fstream>
#include <ncurses.h>
#include "world.hpp"
#include "../state_machine/state.hpp"
#include "../tetramini/tetramini.hpp"
#include "../tetramini/hero.hpp"
#include "../tetramini/smashboy.hpp"
using namespace std;

/**
 * Stato di gioco in cui si gestisce la partita di tetris
 */
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
		int game_over=1;
		int falls;

	public:
		/// Costruttore dello stato
		Partita();

		/// Fa interagire il giocatore con il gioco
		int update(int input);

		/// Fa giocare l'utente a tetris
		int gameplay(int input);

		/// Aggiorna la classifica in caso di game over
		void gameOver();
};

#endif
