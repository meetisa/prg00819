#include "state.hpp"

void State::setDone(int d) {
	done = d;
}

int State::isDone() {
	return done;
}

state State::getNext() {
	return next;
}
