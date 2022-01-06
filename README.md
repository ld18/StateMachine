# StateMachine
UML state machine implementation in C ++. Which allows you to easily define UML states with do-, while- and exit-actions and a plug and play state machine.

The code is split into to part, the State.h/cpp and the StateMachine.h/cpp. 
The State part contains an "abstract" state with implementations for functionalities when entering, reaming and leaving a state. Also, the state transition is here implemented. It is designed that a new custom state should derive of this base state class and override the needed functions. 

The StateMachine handles the states, their transitions and their functions. It does not need any change, when a new state is introduced. 


Example usage:

main.cpp


    #include <iostream>
    #include "StateMachine.h"
    #include "myStates.h"

    using namespace std;

    int main(int argc, char* argv[]) {
      StateMachine sm = StateMachine(new off_State());

      for (int i = 0; i < 10; i++) {
        cout << i << " " << sm.calculateUpdatePeriode() << "ms : ";
        sm.update();
      }
      return 0;
    }


myStates.h

    #pragma once

    #include "State.h"

    class off_State : public State {
    public:
      off_State() { name = "off"; };
      StateAction getNextAction() override;
      State* doLeaveActions() override;
    };

    class startup_State : public State {
    public:
      startup_State() { name = "startup"; };
      StateAction getNextAction() override;
      virtual void doEnterActions() override;
      State* doLeaveActions() override;
    };

    class measure_State : public State {
    public:
      measure_State() { name = "measure"; };
      virtual void doStayActions() override;
    };

    class emergency_State : public State {
    public:
      emergency_State() { name = "emergency"; };
    };


myStates.cpp

    #include "myStates.h"

    StateAction off_State::getNextAction()
    {
      return StateAction::leave;
    }
    State* off_State::doLeaveActions()
    {
      delete State::doLeaveActions();
      return new startup_State();
    }

    StateAction startup_State::getNextAction()
    {
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
    }
    State* startup_State::doLeaveActions()
    {
      delete State::doLeaveActions();
      return new measure_State();
    }

    void measure_State::doStayActions()
    {
      State::doStayActions();
      //meassure and print or do stuff
    }
