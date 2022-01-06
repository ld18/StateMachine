
#include "State.h"
#include <stdlib.h>

StateAction State::getNextAction() {
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

State* State::doLeaveActions() {
	leaftAt = high_resolution_clock::now();
	return nullptr;
};