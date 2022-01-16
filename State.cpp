
#include "State.h"
#include <stdlib.h>

StateAction State::getNextAction(State*& newState) {
	newState = nullptr;
	if (entered) {
		return StateAction::stay;
	}
	else {
		return StateAction::enter;
	}
};

void State::doEnterActions() {
	enteredAt = steady_clock::now();
	lastUpdate = steady_clock::now();
	entered = true;
};

void State::doStayActions() {
	lastUpdate = steady_clock::now();
};

void State::doLeaveActions() {
	leaftAt = steady_clock::now();
	lastUpdate = steady_clock::now();
};