#include "include/state_machine/state_machine.hpp"
using namespace std;

/**
 * Funzione principale del progetto
 */
int main() {
	// per generare numeri casuali
	srand(time(NULL));

	/**
	 * istanzio una macchina a stati
	 * serve per gestire con efficienza le interazioni
	 * tra vari stati del gioco
	*/
	auto machine = StateMachine(MENU);

	machine.game_loop();

	return 0;
}
