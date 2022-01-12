# StateMachine
UML state machine implementation in C ++. Which allows you to easily define UML states with entry-, while- and exit-actions and a plug and play state machine.

The code is split into two part, the State.h/cpp and the StateMachine.h/cpp. 
The State part contains an "abstract" state with implementations for functionalities when entering, reaming and leaving a state. Also, the state transition is here implemented. It is designed that a new custom state should derive of this base state class and override the needed functions. 

The StateMachine parts handles the states, their transitions and their functions. It does not need any changes, when a new state is introduced. 



Example usage:

main.cpp


    #include <iostream>
    #include "StateMachine.h"
    #include "myStates.h"

    using namespace std;

    int main(int argc, char* argv[]) {
        StateMachine sm = StateMachine(new off_State());

        for (int i = 0; i < 10; i++) {
            cout << i << " " << sm.calculateUpdatePeriode() << "ms: \t";
            sm.update();
            cout << endl;
        }
        return 0;
    }


myStates.h

    #pragma once

    #include "State.h"

    class off_State : public State {
    public:
        off_State() { name = "off"; };
        StateAction getNextAction(State*& newState) override;
        void doLeaveActions() override;
    };

    class startup_State : public State {
    public:
        startup_State() { name = "startup"; };
        StateAction getNextAction(State*& newState) override;
        void doEnterActions() override;
        void doLeaveActions() override;
    };

    class measure_State : public State {
    public:
        measure_State() { name = "measure"; };
        void doStayActions() override;
    };


myStates.cpp

    #include "myStates.h"
    #include <iostream>

    using std::cout;

    StateAction off_State::getNextAction(State*& newState)
    {
        newState = new startup_State();
        return StateAction::leave;
    }
    void off_State::doLeaveActions()
    {
        State::doLeaveActions();
        cout << "off_State::doLeaveActions";
    }

    StateAction startup_State::getNextAction(State*& newState)
    {
        newState = new measure_State();
        if (!entered) {
            return StateAction::enter;
        }
        else {
            return StateAction::leave;
        }
    }
    void startup_State::doEnterActions()
    {
        State::doEnterActions();
        cout << "startup_State::doEnterActions";
    }
    void startup_State::doLeaveActions()
    {
        State::doLeaveActions();
        cout << "startup_State::doLeaveActions";
    }

    void measure_State::doStayActions()
    {
        State::doStayActions();
        cout << "measure_State::doStayActions";
    }
