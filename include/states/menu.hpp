#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "../state_machine/state.hpp"
#include "screen.hpp"

/**
 * Stato di gioco inizile, in cui l'utente deve scegliere
 * tra iniziare una nuova partita e il vedere la classifica
 */
class Menu : public State {
	private:
		int ROW_SPACING = 2;

		List options;

		int TEXT_XOFF = 4;
		int TEXT_YOFF = 1;

		const char CRS_CH = '>';
		int CRS_YOFF;
		int CRS_X;
		int CRS_Y;
		int cursor = 0;

	public:
		/// Costruttore dello stato
		Menu();

		/// Stampa le opzioni con il cursore
		void draw();

		/// Fa interagire il giocatore con le opzioni
		int update(int input);
};

#endif
