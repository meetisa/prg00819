#ifndef ABSTRACT_STATE_HPP
#define ABSTRACT_STATE_HPP

#define STATES_LEN 3

typedef enum states_list {
	MENU,
	PARTITA,
	CLASSIFICA
} state;

class State {
	protected:
		int done = 0;
		int quit=0;
		state next;
		state previous;

	public:
		State() {}

		void setDone(int d);
		int isDone();
		void setNext(state n);
		state getNext();
		void Quit();
		int getQuit();

		virtual int update(int input)=0;
};

#endif
