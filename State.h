#pragma once

#include <string>
#include <chrono>

using std::string;
using std::chrono::steady_clock;

/// <value> Action a state can performe, see UML entry, do and exit actions. </value>
enum StateAction {
	enter,
	stay,
	leave
};

/// <summary> Representation of a UML state.  
/// This class is a representation of a UML state, of which you can derive you costum state and use it with the StateMachine. </summary>
class State {
public:
	State() = default;	
	
	virtual ~State() = default;
	
	/// <summary> Get the next action from a state and the next state. 
	/// Check the conditions and calculate if the machine enters into a state, stay in the current one or leaves the current one. </summary>
	/// <param name="newState"> Used to insert the new State, only useed when leaving the state. </param>
	/// <returns> Indicates which action will be performed. </returns>  
	/// <remarks> Need to be fully rewritten by you. </remarks>
	virtual StateAction getNextAction(State*& newState);
	
	/// <summary> Performes the tasks defined when entering a new state. </summary>
	virtual void doEnterActions();
	
	/// <summary> Performes the tasks defined when staying in the current state. </summary>
	virtual void doStayActions();
	
	/// <summary> Performes the tasks defined when leaving a state. </summary>
	virtual void doLeaveActions();

	/// <value> String to describe the state. </value>
	string name = "baseState";

	steady_clock::time_point getEntryTimepoint() const{
		return enteredAt;
	} 

	/// <value> Maximum time between two action calls in ms. </value>
	//uint18_t maxUpdateInterval = 0;

protected:
	/// <value> Internal boolean to differentiate the enter action from a stay action. </value>
	/// <remarks> Have a look into State::getNextAction(). </remarks>
	bool entered = false;

	/// <value> Timepoint when the current state was enterd. </value>
	/// <remarks> Should be set in doEnterActions(). </remarks>
	steady_clock::time_point enteredAt;
	
	/// <value> Timepoint when the last state was left. </value>
	/// <remarks> Should be set in doLeaveActions(). </remarks>
	steady_clock::time_point leaftAt;
	
	/// <value> Timepoint when the last action was called. </value>
	/// <remarks> Should be set in do******Actions(). </remarks>
	steady_clock::time_point lastUpdate;
};
