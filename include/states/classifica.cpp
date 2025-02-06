#include "classifica.hpp"

/**
 * Costruttore della classe
 */
Classifica::Classifica() : State() {

	/* */
	char tmp_pos[MAX_LEN_POS];
	int i_pos = 0;

	/* */
	char tmp_nm[MAX_LEN_NAME];
	int i_nm = 0;

	/* */
	char tmp_pnt[MAX_LEN_PNT];
	int i_pnt = 0;

	/* */
	char tmp_dt[MAX_LEN_DATE];
	int i_dt = 0;

	/* */
	char line[MAX_LEN_ALL];
	int i, line_len, x=0;

	player *iter;
	iter = head;

	ifile.open(filename);
	while(ifile.getline(line, sizeof(line))) {

		x = 0;
		i_pos = 0;
		i_nm = 0;
		i_pnt = 0;
		i_dt = 0;

		players_len++;
		line_len = strlen(line);
		ch_file_len += line_len;

		/*
		 * Ogni riga del file corrisponde a un nodo
		 * della lista concatenata head di tipo player
		 * Quindi nel for analizzo la riga
		 * e attraverso il carattare speciale '@'
		 * si riescono a ricavare tutti i campi
		 * ovviamente i campi devono essere in ordine nella stringa
		 */

		for(i=0; i<line_len; i++) {
			if(line[i] == cols_d)
				x++;
			else if(x == 0)
				tmp_pos[i_pos++] = line[i];
			else if(x == 1)
				tmp_nm[i_nm++] = line[i];
			else if (x == 2)
				tmp_pnt[i_pnt++] = line[i];
			else if(x == 3)
				tmp_dt[i_dt++] = line[i];
		}


		/*
		 * Se il for finisce signica che la riga è finita
		 * quindi le stringhe di ogni campo sono concluse
		 * e si possono trasferire nel nodo della lista
		 */

		tmp_pos[i_pos] = '\0';
		iter->pos = atoi(tmp_pos);

		tmp_nm[i_nm] = '\0';
		strcpy(iter->name, tmp_nm);

		tmp_pnt[i_pnt] = '\0';
		iter->points = atoi(tmp_pnt);

		tmp_dt[i_dt] = '\0';
		strcpy(iter->date, tmp_dt);

		strcpy(iter->all, line);


		/*
		 * Viene creato il nodo successivo della lista,
		 * inizialmente vuoto
		 */

		iter->next = new player;
		iter->next->next = NULL;
		iter = iter->next;
	}
	ifile.close();

	updateAllPlayers();

	chart.init(
		all_players,
		ROW_SPACING,
		TEXT_XOFF,
		TEXT_YOFF,
		borders
	);
	chart.setInCenter();
}

/**
 * Stampa la classifica nel terminale
 */
void Classifica::display() {
	chart.show_list();
}

/**
 * Funzione in cui l'utente può interagire con lo stato
 * @returns il tasto premuto dall'utente
 */
int Classifica::update(int input) {
	/*
	 * Utilizzando una macchina a stati
	 * posso agire diversamente a seconda
	 * dello stato precedente:
	 * se ho appena finito una partita chiedo il nome all'utente
	 * invece si può vedere la classifica direttamente dal menu
	 *
	 */
	if(previous == MENU)
		display();
	else
		addPlayer();

	return 0;
}

/**
 * Fa immetere all'utente il suo nome nel terminale
 * @param new_name[in] il nuovo nome utente
 */
void Classifica::get_new_name(char name[]) {

	int w=50;
	int h = 3;
	Screen insert_name;

	echo();

	insert_name.init(w, h, 0, 0, borders);
	insert_name.setInCenter();

	insert_name.show();

	mvwscanw(insert_name.win, 1, 1, "%s", name);

	noecho();

	insert_name.destroy();
}

/**
 * Aggiunge un nuovo giocatore in classifica
 */
void Classifica::addPlayer() {

	player *iter;

	char name[MAX_LEN_NAME];
	get_new_name(name);

	int i=0, x=0;

	/* */
	char line[MAX_LEN_ALL];
	int i_ln = 0, line_len;

	/* */
	char tmp_dt[MAX_LEN_DATE];
	int i_dt = 0;

	/* */
	char tmp_pnt[MAX_LEN_PNT];
	int i_pnt = 0;

	ifile.open(filename);
	while(ifile.getline(line, sizeof(line))) {
		if(i++ >= players_len) {

			line_len = strlen(line);
			ch_file_len += line_len;

			for(i_ln=0; i_ln < line_len; i_ln++) {
				if(line[i_ln] == cols_d)
					x++;
				else if(x==0)
					tmp_pnt[i_pnt++] = line[i_ln];
				else if(x==1)
					tmp_dt[i_dt++] = line[i_ln];
			}

			tmp_pnt[i_pnt]  = '\0';
			tmp_dt[i_dt] = '\0';
		}
	}
	ifile.close();

	insertPlayer(name, atoi(tmp_pnt), tmp_dt);

	ofile.open(filename);
	for(iter=head; iter->next!=NULL; iter=iter->next) {
		ofile << iter->all << rows_d;
	}
	ofile.close();

	updateAllPlayers();

	chart.update_list(all_players);
	chart.setInCenter();

	setDone(1);
}

/**
 * Inserisce un utente nella lista concatenata
 */
void Classifica::insertPlayer(char name[], int points, char date[]) {
	player *tmp, *iter;
	int pos=1;

	tmp = new player;
	strcpy(tmp->name, name);
	tmp->points = points;
	strcpy(tmp->date, date);

	if(points >= head->points) {
		tmp->next = head;
		head = tmp;
	}
	else {
		for(iter=head; iter->next!=NULL; iter=iter->next) {
			if(points < iter->points && points > iter->next->points) {
				tmp->next = iter->next;
				iter->next = tmp;
				break;
			}
		}
	}

	for(iter=head; iter->next!=NULL; iter=iter->next) {
		iter->pos = pos++;

		sprintf(iter->all, "%d%c%s%c%d%c%s",
			    iter->pos, cols_d,
				iter->name, cols_d,
				iter->points, cols_d,
		        iter->date
		);
	}
}

/**
 * Aggiorna la stringa che contiene tutti i giocatori
 */
void Classifica::updateAllPlayers() {
	player *iter;

	char titoli[] = "Posizione@Username@Punteggio@Data\n";
	int tit_len = strlen(titoli);

	all_players = new char[tit_len + ch_file_len + players_len];
	all_players[0] = '\0';

	strcat(all_players, titoli);

	for(iter=head; iter->next!=NULL; iter=iter->next) {
		strcat(all_players, iter->all);
		strcat(all_players, "\n");
	}
}
