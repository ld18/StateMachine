
#include "StateMachine.h"
#include <stdlib.h>
#include <ctime>
#include <type_traits>

StateMachine::StateMachine(State* initialState)
{
	currentState = initialState;
	timeStamps = { steady_clock::now() };
}

void StateMachine::update()
{
	movingAvgIndex = (movingAvgIndex + 1) % movingAvgLength;
	timeStamps[movingAvgIndex] = steady_clock::now();

	State* newState = nullptr;
	StateAction action = currentState->getNextAction(newState);
	switch (action)
	{
	case enter:
		currentState->doEnterActions();
		break;
	case stay:
		currentState->doStayActions();
		break;
	case leave:
		currentState->doLeaveActions();
		delete currentState;
		currentState = newState;
		break;
	default:
		break;
	}
}

int StateMachine::calculateUpdatePeriode()
{
	duration<double> sumT = duration<double>(0.0);
	for (int i = 0; i < movingAvgLength - 1; i++) {
		sumT += timeStamps[(movingAvgIndex - i + movingAvgLength) % movingAvgLength] - timeStamps[(movingAvgIndex - i - 1 + movingAvgLength) % movingAvgLength];
	}
	return sumT.count() * 1000 / (movingAvgLength - 1);
}
