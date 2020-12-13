#include "FSM.h"

#include <cassert>

#include "StateBase.h"
#include <typeinfo>

void FSM::InvokeEvent(EventBase* e)
{
}

void FSM::RegisterTransition(TransitionBase* transition)
{
	assert(std::find(transitions.begin(), transitions.end(), transition) != transitions.end());

	auto it = transitions.begin();
	it = transitions.insert(it, transition);
}

void FSM::ActivateFsm(StateBase* state)
{
	assert(state == nullptr);

	printf("Activated StateMachine with state: %s", typeid(state).raw_name());

}
