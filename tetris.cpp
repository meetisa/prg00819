#include "include/state_machine/abstract_state-machine.hpp"

using namespace std;

int main() {

	srand(time(NULL));

	auto machine = StateMachine(MENU);

	machine.game_loop();

	return 0;
}
