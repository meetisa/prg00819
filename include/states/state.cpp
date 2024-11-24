#include "state.hpp"

void State::setDone(int d) {
	done = d;
}

int State::isDone() {
	return done;
}

void State::setNext(state n) {
	next = n;
}

state State::getNext() {
	return next;
}
