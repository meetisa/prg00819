#include "classifica.hpp"

/**
 * Costruttore della classe
 */
Classifica::Classifica() : State() {

	setNext(MENU);

	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);

	player *iter;
	iter = head;

	int delimiter=0;
	int i, j=0, line_len, p;
	char ch, riga[100], tmp_name[100], tmp_points[100];

	ifile.open(filename);

	while(ifile.getline(riga, sizeof(riga), '\n')) {

		length++;
		line_len = strlen(riga);
		total_len += line_len;

		for(i=0; i<line_len; i++) {
			if(riga[i] == splitter) {
				delimiter = 1;
				tmp_name[i] = '\0';
			}
			else if(!delimiter)
				tmp_name[i] = riga[i];
			else
				tmp_points[j++] = riga[i];
		}

		tmp_points[j] = '\0';

		strcpy(iter->all, riga);
		strcpy(iter->name, tmp_name);
		iter->points = atoi(tmp_points);

		iter->next = new player;
		iter->next->next = NULL;
		iter = iter->next;

		delimiter = 0;
		j = 0;

	}

	ifile.close();

	j=0;
	all_players = new char[total_len + length];

	for(iter=head; iter!=NULL; iter=iter->next) {
		for(i=0; i<strlen(iter->all); i++)
			all_players[j++] = iter->all[i];
		all_players[j++] = '\n';
	}

	all_players[j-2] = '\0';

	chart.init(
		all_players,
		'@',
		ROW_SPACING,
		TEXT_XOFF,
		TEXT_YOFF,
		"||--++++"
	);
	chart.setInCenter();
}

/**
 * Stampa la classifica nel terminale
 */
void Classifica::display() {
	int pair = 1;
	wattron(chart.win, COLOR_PAIR(pair));
	chart.show_list();
	wattroff(chart.win, COLOR_PAIR(pair));
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

	char line[100];
	int p, i=0;

	ifile.open(filename);
	while(ifile.getline(line, sizeof(line))) {
		i++;
		if(i >= length)
			p = atoi(line);
	}
	ifile.close();

	insertPlayer(name, p);

	ofile.open(filename);
	for(iter=head; iter->next!=NULL; iter=iter->next) {
		ofile << iter->name << '@' << iter->points << '@' << endl;
	}
	ofile.close();

	i=0;
	all_players = new char[999999];

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
void Classifica::insertPlayer(char name[], int points) {
	player *tmp, *iter;
	char str_points[100];

	tmp = new player;
	strcpy(tmp->name, name);
	tmp->points = points;

	sprintf(tmp->all, "%s@%d", name, points);

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
