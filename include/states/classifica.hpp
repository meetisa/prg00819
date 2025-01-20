#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

#include <string.h>
#include <fstream>
#include <ncurses.h>
#include "../state_machine/state.hpp"
#include "screen.hpp"
using namespace std;

typedef struct pnode {
	pnode *next;
	char all[100];
	char name[50];
	int points;
} player;

/**
 * Stato per la classifica di gioco
 */
class Classifica : public State {
	private:
		const char *filename = "classifica.txt";
		const char splitter = '@';
		ofstream ofile;
		ifstream ifile;

		player *head = new player;

		char *all_players;

		List chart;

		int ROW_SPACING = 2;
		int TEXT_XOFF = 3;
		int TEXT_YOFF = 1;

		int total_len=0;
		int length=0;

	public:

		/// Costruttore dello stato
		Classifica();

		/// Stampa la classifica nel terminale
		void display();

		/// Fa interagire l'utente con lo stato di giocos
		int update(int input);

		/// ???
		player gameOverScreen(int points);

		/// Fa immettere all'utente il suo nome per la classifica
		void get_new_name(char name[]);

		/// Aggiunge un nuovo giocatore nella classifica
		void addPlayer();

		/// Inserisce un giocatore nellla lista concatenata
		void insertPlayer(char name[], int points);
};

#endif
