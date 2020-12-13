#pragma once
#include <vector>

#include "TransitionBase.h"

class EventBase;
class StateBase;

using namespace Tmpl8;
class FSM
{
protected:
	std::vector<TransitionBase*> transitions;
	StateBase* activeState = nullptr;

public:
	void InvokeEvent(EventBase* e);

	void RegisterTransition(TransitionBase* transition);
	void ActivateFsm(StateBase* state);
};




class Event //StateMachine containing Payload data
{

};
