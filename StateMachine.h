#pragma once

#include "State.h"
#include <chrono>

/// <value> Length of the moving averange used to calculate the update periode. </value>
#define movingAvgLength 2

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::steady_clock;

/// <summary> Update the state machine. 
/// Calculates the next state transition/action and performed the state functions. </summary>
/// <remarks> No need to change anything here, all the work is done in the State.h/cpp  </remarks>
class StateMachine {
public:
	StateMachine(State* initialState);

	/// <summary> Update the state machine. 
	/// Calculates the next state transition/action and performed the state functions. </summary>
	void update();

	/// <summary> Calculates the time periode between the update calls. 
	/// Is smoothed by an moving averange. </summary>
	/// <returns> Periode in ms </returns>
	/// <remarks> Have a look at movingAvgLength </remarks>
	int calculateUpdatePeriode();

	string getStateName(){
		return currentState->name;
	}
	~StateMachine() {
		delete currentState;
	}
private:
	/// <value> Holds the current state of the state machine. </value>
	/// <remarks> Needs to  be set tothe begin </remarks>
	State* currentState = new State();

	steady_clock::time_point timeStamps[movingAvgLength] = { steady_clock::now() };
	int movingAvgIndex = 0;
};