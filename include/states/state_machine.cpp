#include "state_machine.hpp"

StateMachine::StateMachine(state start) {
	int i;
	for(i=0; i<STATES_LEN; i++)
		states[i] = NULL;
	current_state = start;

	states[0] = new Menu();
	states[1] = new Partita();
	states[2] = new Classifica();

	current = states[start];
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
	int ch;

	while(!done) {
		ch = getch();

		switch(ch) {
			case 'q':
				done = 1;
			break;

			case ' ':
				current->setDone(1);
			break;
		}

		update(ch);
		refresh();
	}
}
