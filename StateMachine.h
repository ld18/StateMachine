#pragma once

#include "State.h"
#include <chrono>
#include <memory>
#include <utility>

/// <value> Length of the moving averange used to calculate the update periode. </value>
#define movingAvgLength 3

using std::chrono::duration;
using std::chrono::steady_clock;
using std::unique_ptr;
using std::move;

/// <summary> Update the state machine. 
/// Calculates the next state transition/action and performed the state functions. </summary>
/// <remarks> No need to change anything here, all the work is done in the State.h/cpp  </remarks>
class StateMachine {
public:
	StateMachine() = default;

	/// <summary> Inits the state machine. 
	/// <value> Holds the initial state of the state machine. </value>
	/// <remarks> Needs to  be set to the start state </remarks>
	/// Must be called befor the first update </summary>
	void init(State* initialState);

	/// <summary> Update the state machine. 
	/// Calculates the next state transition/action and performed the state functions. </summary>
	void update();

	/// <summary> Calculates the time periode between the update calls. 
	/// Is smoothed by an moving averange. </summary>
	/// <returns> Periode in ms </returns>
	/// <remarks> Have a look at movingAvgLength </remarks>
	int calculateUpdatePeriode() const;

	string getStateName() const{
		return currentState->name;
	}
	
private:
	/// <value> Holds the current state of the state machine. </value>
	unique_ptr<State> currentState;

	steady_clock::time_point timeStamps[movingAvgLength];

	int movingAvgIndex = 0;
};