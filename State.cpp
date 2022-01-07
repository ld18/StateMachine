
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
	enteredAt = high_resolution_clock::now();
	entered = true;
};

void State::doStayActions() {
};

void State::doLeaveActions() {
	leaftAt = high_resolution_clock::now();
};