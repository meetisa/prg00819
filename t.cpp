#include <iostream>
#include <ncurses.h>
using namespace std;

typedef enum _state {
	STATE1=0,
	STATE2,
	STATE3
} state;

class State {
	//private:
	public:
		int done = 0;
		int quit = 0;
		state next;
		state previous;
		virtual void update() {
			mvprintw(0, 0, "state0");
		}
};

class St1 : public State {
	public:
		St1() {
			next = STATE3;
		}

		void update() {
			mvprintw(0, 0, "state1");
		}
};

class St2 : public State {
	public:
		St2() {
			next = STATE1;
		}

		void update() {
			mvprintw(0, 0, "state2");
		}
};

class St3 : public State {
	public:
		St3() {
			next = STATE2;
		}


		void update() {
			mvprintw(0, 0, "state3");
		}
};

class StateMachine {
	private:
		int done = 0;
		state current_state;
		State *current;
		State *states[3];

			St1 t1;
			St2 t2;
			St3 t3;
			State *cstate;

	public:
		StateMachine(state start) {
			for(int i=0; i<3; i++)
				states[i] = NULL;
			current_state = start;

			states[0] = new St1();
			states[1] = new St2();
			states[2] = new St3();

			current = states[start];
		}

		void flip() {
			current->done = 0;

			state previous;
			previous = current_state;
			current_state = current->next;
			current->previous = previous;

			current = states[current_state];
		}

		void update() {
			if(current->done)
				flip();

			current->update();
		}

		void game_loop() {
			int ch;

			while(!done) {

				ch = getch();
				switch(ch) {
					case 'q':
						done = 1;
					break;

					case 'x':
						current->done = 1;
					break;
				}

				update();

				refresh();
			}
		}
};

int main() {
	//initialization functions
	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	curs_set(0); //invisible cursor

	auto m = StateMachine(STATE1);

	m.game_loop();

	endwin();
	return 0;
}
