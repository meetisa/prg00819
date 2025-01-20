#include "state_machine.hpp"

/**
 * Costruttore della classe StateMachine
 * @param start Lo stato con cui partirà il gioco
 */
StateMachine::StateMachine(state start) {

	// inizializzo tutte le funzioni di ncurses
	init_ncurses();

	int i;
	for(i=0; i<STATES_LEN; i++)
		states[i] = NULL;
	current_state = start;

	states[0] = new Menu();
	states[1] = new Partita();
	states[2] = new Classifica();

	current = states[start];
}

/**
 * Inizializza tutte le funzioni di ncurses necessarie
 */
void StateMachine::init_ncurses() {
	initscr(); // avvia ncurses

	cbreak(); // per controllare gli input di controllo (CTRL-Z, CTRL-C)

	noecho(); // gli input non vengono riprodotti nel terminale

	nodelay(stdscr, TRUE); // fa sì che getch non aspetti per l'input

	keypad(stdscr, TRUE); // fa leggere tutti i pulsanti della tastiera

	curs_set(0); // rende il cursore invisibile

	if(has_colors() == TRUE)
		start_color(); // per i colori
}

/**
 * Cambia lo stato attuale del gioco
 */
void StateMachine::flip() {
	state previous;
	current->setDone(0);

	previous = current_state;

	current_state = current->getNext();
	current = states[current_state];

	current->setPrev(previous);
}

/**
 * Aggiorna lo stato attuale e controlla
 * che non ci sia bisogno di cambiarlo
 */
void StateMachine::update(int input) {
	if(current->getQuit()) {
		done = 1;
		return;
	}
	if(current->isDone())
		flip();

	current->update(input);
}

/**
 * Fa partire il gioco intero attraverso un loop infinito
 */
void StateMachine::game_loop() {
	int ch = 0;

	refresh();

	while(!done) {

		if(ch == 'q')
			done = 1;

		refresh();
		update(ch);

		ch = getch();
	}

	endwin();
}
