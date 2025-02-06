#include <iostream>
#include <fstream>
#include <string.h>
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

typedef struct node {
	char name[100];
	int points;
	node *next;
} player;

typedef struct ff {
	char *str[50];
	int max_len;
} field;

int main() {
	//initialization functions
	// initscr();
	// start_color();
	// raw();
	// cbreak();
	// noecho();
	// nodelay(stdscr, TRUE);
	// keypad(stdscr, TRUE);
 //
	// curs_set(0); //invisible cursor
 //
	// auto m = StateMachine(STATE1);
 //
	// m.game_loop();
 //
	// endwin();


	// const char *filename = "classifica.txt";
	// const char *name = "coglione";
	// int np = 560;
	// char pname[100];
	// char points[100];
	// ofstream ofile;
	// ifstream ifile;

	// char cols_d = '@';
	// char rows_d = '\n';
 //
	// // char s[] = "pippo@210@29/11@\nfranco@123@28/11@\nclaudio@45@23/11@\n";
	// char s[] = "Nuova partita@\nClassifica@\nEsci@\n";
	// //3 lunghezze di cui tener conto
 //
	// int len=0, max=0;
	// int maxf[3], lenf[3];
	// for(int i=0; i<3; i++) {
	// 	maxf[i] = 0;
	// 	lenf[i] = 0;
	// }
	// int total_len = strlen(s);
	// int xt=0;
	// for(int i=0; i<total_len; i++) {
	// 	if(s[i] == rows_d) {
	// 		if(len > max)
	// 			max = len;
	// 		len = 0;
	// 	}
	// 	else {
	// 		len += s[i] != cols_d;
	// 	}
	// 	// if(s[i] == cols_d) {
	// 	// 	if(lenf[xt] > maxf[xt])
	// 	// 		maxf[xt] = lenf[xt];
	// 	// 	cout << lenf[xt] << " " << xt << "\t";
	// 	// 	xt++;
	// 	// }
	// 	// else if(s[i] == rows_d) {
	// 	// 	xt = 0;
	// 	// 	for(int j=0; j<3; j++)
	// 	// 		lenf[j] = 0;
	// 	// 	cout << endl;
	// 	// }
	// 	// else
	// 	// 	lenf[xt]++;
	// }
	// cout << max;
	// cout << endl;

	// char tmp[50];
	// int i, i_f=0, n_f=0, j=0, j_f=0;
	// int xt=0, yt=0; // t di tabella
	// int l=0;
	// int total_len = strlen(s);
 //
	// // 3 colonne
	// field f[3];
	// for(i=0; i<3; i++)
	// 	f[i].max_len = 0;
 //
	// for(i=0; i<total_len; i++) {
	// 	if(s[i] == cols_d) {
	// 		// tronco la cella attuale
	// 		tmp[j] = '\0';
 //
	// 		l = strlen(tmp);
	// 		if(l > f[xt].max_len)
	// 			f[xt].max_len = l;
 //
	// 		// inizializzo nuova cella
	// 		f[xt].str[yt] = new char[60];
 //
	// 		strcpy(f[xt].str[yt], tmp);
	// 		xt++;
 //
	// 		// cancello la cella attuale per passare alla prossima
	// 		tmp[0] = '\0';
	// 		j=0;
	// 	}
	// 	else if(s[i] == rows_d) {
	// 		// nuova riga, colonne azzerate
	// 		xt = 0;
	// 		yt++;
	// 	}
	// 	else {
	// 		tmp[j++] = s[i];
	// 	}
	// }
 //
	// for(i=0; i<3; i++) {
	// 	for(j=0; j<yt+1; j++)
	// 		cout << f[i].str[j] << endl;
	// 	cout << f[i].max_len << endl;
	// }
 //
	// cout << endl;
 //
	// ifile.open(filename);
	// char ch;
	// char *players;
	// players = new char[1000];
	// int i=0, ch_len=0, len=0;
 //
	// while(!ifile.eof()) {
	// 	ifile.get();
	// 	ch_len++;
	// }
 //
 //
	// ifile.clear();
	// ifile.seekg(0);
 //
	// while(!ifile.eof()) {
	// 	ifile.get(players[i]);
	// 	if(players[i++] == '\n')
	// 		len++;
	// }
 //
	// players[i-2] = '\0';
 //
	// cout << players;

	// 		iter->next = new player;
	// player *head;
	// player *iter;
	// head = new player;
	// head->next = NULL;
	// iter = head;
 //
	// ifile.open(filename);
	// char ch;
	// char riga[100];
	// int del=0, j=0, len;
 //
	// while(ifile.getline(riga, sizeof(riga), '\n')) {
	// 	len = strlen(riga);
	// 	char nm[len], pn[len];
	// 	for(int i=0; i<len; i++) {
	// 		if(riga[i] == '@') {
	// 			nm[i] = '\0';
	// 			del=1;
	// 		}
	// 		else if(!del) {
	// 			nm[i] = riga[i];
	// 		}
	// 		else {
	// 			pn[j++] = riga[i];
	// 		}
	// 	}
	// 	strcpy(iter->name, nm);
	// 	iter->points = atoi(pn);
 //
	// 	iter->next = new player;
	// 	iter->next->next = NULL;
	// 	iter = iter->next;
 //
	// 	del = 0;
	// 	j = 0;
	// }
 //
	// for(iter=head; iter->next!=NULL; iter=iter->next)
	// 	cout << iter->name << " " << iter->points << endl;


	// int p, n=0, i=0, j=0;
	// while(!ifile.eof()) {
	// 	ifile.get(ch);
 //
	// 	if(n)
	// 		points[i++] = ch;
	// 	else
	// 		pname[j++] = ch;
 //
	// 	if(n && ch == '\n') {
	// 		points[i] = '\0';
	// 		i=0;
	// 		n = 0;
	// 		p = atoi(points);
	// 		iter->points = p;
 //
	// 		iter->next = new player;
	// 		iter->next->next = NULL;
	// 		iter = iter->next;
	// 	}
 //
	// 	if(ch == '@') {
	// 		pname[j-1] = '\0';
	// 		j=0;
	// 		n=1;
	// 		strcpy(iter->name, pname);
	// 	}
	// }

	// ifile.close();

	// ofile.open(filename);
 //
	// for(iter=head; iter->next!=NULL; iter=iter->next) {
	// 	ofile << iter->name << '@' << iter->points << endl;
 //
	// 	if(np < iter->points && np > iter->next->points)
	// 		ofile << name << '@' << np << endl;
	// }
 //
	// ofile.close();

	const char *filename = "test.txt";
	ifstream ifile;
	ofstream ofile;

	ifile.open(filename);
	char line[50];
	ifile >> line;
	cout << line;

	ifile.close();

	return 0;
}
