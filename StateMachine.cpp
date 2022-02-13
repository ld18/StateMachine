
#include "StateMachine.h"

void StateMachine::init(State* initialState){	
	timeStamps[0] = steady_clock::now();
	movingAvgIndex = 0;
	currentState = unique_ptr<State>(move(initialState));
	initialState = nullptr;
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
		currentState = unique_ptr<State>(move(newState));
		break;
	default:
		break;
	}
}

int StateMachine::calculateUpdatePeriode() const
{
	duration<float> timeSum;
	for (int i = 0; i < movingAvgLength - 1; i++) {
		if(timeStamps[(movingAvgIndex + i) % movingAvgLength].time_since_epoch().count() > 0){
			timeSum += timeStamps[(movingAvgIndex - i + movingAvgLength) % movingAvgLength] - timeStamps[(movingAvgIndex - i - 1 + movingAvgLength) % movingAvgLength];
		}else{	//Not enougth timestamps (array is not primed/filled)
			return -1;
		}
	}
	return (timeSum.count() * 1000) / (movingAvgLength - 1);
}
