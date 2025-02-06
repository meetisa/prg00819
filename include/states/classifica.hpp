#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

#include <string.h>
#include <fstream>
#include <ncurses.h>
#include "../state_machine/state.hpp"
#include "screen.hpp"
using namespace std;

#define MAX_LEN_ALL 50

#define MAX_LEN_POS 5
#define MAX_LEN_NAME 23
#define MAX_LEN_PNT 10
#define MAX_LEN_DATE 12

typedef struct pnode {
	pnode *next;
	char all[MAX_LEN_ALL];
	char name[MAX_LEN_NAME];
	char date[MAX_LEN_DATE];
	int points;
	int pos;
} player;

/**
 * Stato per la classifica di gioco
 */
class Classifica : public State {
	private:
		const char *filename = "classifica.txt";
		const char cols_d = '@';
		const char rows_d = '\n';
		ofstream ofile;
		ifstream ifile;

		player *head = new player;

		char *all_players;

		List chart;

		const int ROW_SPACING = 2;
		const int TEXT_XOFF = 2;
		const int TEXT_YOFF = 1;

		const char *borders = "||--++++";

		int ch_file_len=0;
		int players_len=0;

	public:

		/// Costruttore dello stato
		Classifica();

		/// Stampa la classifica nel terminale
		void display();

		/// Fa interagire l'utente con lo stato di giocos
		int update(int input);

		/// Fa immettere all'utente il suo nome per la classifica
		void get_new_name(char name[]);

		/// Aggiunge un nuovo giocatore nella classifica
		void addPlayer();

		/// Inserisce un giocatore nellla lista concatenata
		void insertPlayer(char name[], int points, char date[]);

		void updateAllPlayers();
};

#endif
