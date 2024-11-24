#include "state_machine.hpp"

StateMachine::StateMachine(state start) {
	int i;
	for(i=0; i<STATES_LEN; i++)
		states[i] = NULL;
	current_state = start;

	init_ncurses();

	states[0] = new Menu();
	states[1] = new Partita();
	states[2] = new Classifica();

	current = states[start];

}

void StateMachine::init_ncurses() {
	//initialization functions
	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	curs_set(0); //invisible cursor
}

void StateMachine::flip() {
	current->setDone(0);
	current_state = current->getNext();
	current = states[current_state];
}


void StateMachine::update(int input) {
	if(current->isDone())
		flip();

	current->update(input);
}

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
