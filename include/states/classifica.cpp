#include "classifica.hpp"

/**
 * Costruttore della classe
 */
Classifica::Classifica() : State() {

	player *iter;
	iter = head;

	int i_all = 0;

	/* */
	char tmp_nm[50];
	int i_nm = 0;

	/* */
	char tmp_pnt[15];
	int i_pnt = 0;

	/* */
	char tmp_dt[12];
	int i_dt = 0;

	/* */
	char riga[100];
	int i, line_len, x=0;


	ifile.open(filename);

	while(ifile.getline(riga, sizeof(riga))) {

		length++;
		line_len = strlen(riga);
		total_len += line_len;

		for(i=0; i<line_len; i++) {
			if(riga[i] == cols_d) {
				x++;
				tmp_nm[i] = '\0';
			}
			else if(x == 0)
				tmp_nm[i_nm] = riga[i];
			else if (x == 1)
				tmp_pnt[i_pnt++] = riga[i];
			else if(x == 2)
				tmp_dt[i_dt++] = riga[i];
		}

		tmp_pnt[i_pnt] = '\0';
		tmp_dt[i_dt] = '\0';

		strcpy(iter->all, riga);
		strcpy(iter->name, tmp_nm);
		iter->points = atoi(tmp_pnt);
		strcpy(iter->date, tmp_dt);

		iter->next = new player;
		iter->next->next = NULL;
		iter = iter->next;

		x = 0;

		i_nm = 0;
		i_pnt = 0;
		i_dt = 0;
	}

	ifile.close();


	all_players = new char[total_len + length];

	for(iter=head; iter!=NULL; iter=iter->next) {
		for(i=0; i<strlen(iter->all); i++)
			all_players[i_all++] = iter->all[i];
		all_players[i_all++] = '\n';
	}

	all_players[i_all-2] = '\0';

	chart.init(
		all_players,
		ROW_SPACING,
		TEXT_XOFF,
		TEXT_YOFF,
		"||--++++"
	);
	chart.setInCenter();

	setNext(MENU);
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
	if(previous == MENU)
		display();
	else
		addPlayer();

	return 0;
}

/**
 * Fa immetere all'utente il suo nome nel terminale
 * @param new_name il nuovo nome utente
 */
void Classifica::get_new_name(char name[]) {
	Screen insert_name;

	echo();

	insert_name.init(50, 3, 0, 0, "||--++++");
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
	char name[50];
	get_new_name(name);

	int i=0, split=0;

	/* */
	char line[100];
	int i_ln = 0;

	/* */
	char tmp_dt[12];
	int i_dt = 0;

	/* */
	char tmp_pnt[15];
	int i_pnt = 0;

	ifile.open(filename);
	while(ifile.getline(line, sizeof(line))) {
		if(i++ >= length) {
			total_len += strlen(line);
			for(i_ln=0; i_ln < strlen(line); i_ln++) {
				if(line[i_ln] == cols_d)
					split = 1;
				else if(!split)
					tmp_pnt[i_pnt++] = line[i_ln];
				else
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

	i=0;
	all_players = new char[total_len + length];

	ifile.open(filename);
	while(!ifile.eof())
		ifile.get(all_players[i++]);
	ifile.close();
	all_players[i-2] = '\0';

	chart.update_list(all_players);
	chart.setInCenter();

	setDone(1);
}

/**
 * Inserisce un utente nella lista concatenata
 */
void Classifica::insertPlayer(char name[], int points, char date[]) {
	player *tmp, *iter;

	tmp = new player;
	strcpy(tmp->name, name);
	tmp->points = points;
	strcpy(tmp->date, date);

	sprintf(tmp->all, "%s%c%d%c%s", name, cols_d, points, cols_d, date);

	if(points >= head->points) {
		tmp->next = head;
		head = tmp;
	}
	else {
		for(iter=head; iter->next!=NULL; iter=iter->next) {
			if(points < iter->points && points > iter->next->points) {
				tmp->next = iter->next;
				iter->next = tmp;
			}
		}
	}
}
