#ifndef STATE_HPP
#define STATE_HPP

#define STATES_LEN 3

/**
 * Una lista degli stati di gioco
 * ho fatto un tipo a parte per rendere più chiaro il codice
 */
typedef enum states_list {
	MENU,
	PARTITA,
	CLASSIFICA
} state;

/**
 * Classe astratta dello stato di gioco.
 * Ogni stato ha una classe concreta apposta in un suo file.
 */
class State {
	protected:
		int done = 0;
		int quit = 0;
		state next;
		state previous;

	public:

		/// Costruttore della classe
		State() {}

		/// Comunica che lo stato ha finito
		void setDone(int d);

		/// Controlla se lo staato ha finito
		int isDone();

		/// Decide quale sarà il prossimo stato
		void setNext(state n);

		/// Fa sapere il prossimo stato di gioco
		state getNext();

		/// Decide lo stato precedente
		void setPrev(state prev);

		/// Esce definitivamente dal gioco
		void Quit();

		/// Fa sapere se bisogna uscire dal gioco
		int getQuit();

		/// Funzione astratta
		virtual int update(int input)=0;
};

#endif
