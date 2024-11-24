#include <iostream>
#include <ctime>
#include <ncurses.h>
#include "include/tetramini/tetramini.hpp"
#include "include/states/gameplay.hpp"
#include "include/states/menu.hpp"
#include "include/states/classifica.hpp"
#include "include/states/state_machine.hpp"
using namespace std;

int main() {

	auto machine = StateMachine(MENU);

	machine.game_loop();

	return 0;
}
