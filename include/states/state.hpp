#ifndef STATE_HPP
#define STATE_HPP

#define STATES_LEN 3

typedef enum _state {
	MENU,
	PARTITA,
	CLASSIFICA
} state;

class State {
	private:
		int done = 0;
		state next;

	public:
		State();

		void setDone(int d);
		int isDone();
		state getNext();
		virtual void update(int input)=0;
};

#endif
