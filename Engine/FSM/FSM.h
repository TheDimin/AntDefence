#pragma once
#include <cassert>
#include <memory>
#include <vector>
#include "../template.h"
#include "State.h"

#define StateCallWrapper(NAME,PARAM_TYPE,PARAM_NAME)	\
	void NAME(PARAM_TYPE PARAM_NAME){					\
		if (activeState != nullptr)						\
			activeState->NAME(PARAM_NAME);				\
	}

#define GuardCastCheck(Type,Name)						\
	Type* Name = dynamic_cast<Type*>(event);		\
		if (Name == nullptr) return false;				\

#define DefaultGuardCastCheck(Type)						\
	[](Event* event)									\
	{													\
		GuardCastCheck(Type, castedEvent);				\
														\
		return true;									\
	}													\

namespace Tmpl8 {
	class Surface;
}

template<typename Transition, typename Event, typename State>
class FSM : IRenderable, ITickable
{
protected:
	std::vector<std::unique_ptr<Transition>> transitions;
	std::vector<std::unique_ptr<State>> states;
	State* activeState = nullptr;

public:
	State* GetState() const { return activeState; }
	void InvokeEvent(Event* e)
	{
		for (auto& element : transitions)
		{
			if (element.get()->SourceState != activeState)
				continue;

			if (element->TransitionGuard(e))
			{
				activeState->OnStateExit(e);
				element->TransitionAction(e);
				element->TargetState->OnStateEnter(e);
				activeState = element->TargetState;
				//done with the event object, destroy it
				delete e;
				return;
			}
		}

		assert(false && "Failed to find valid transistion");
	}

	void RegisterTransition(Transition* transition)
	{
		assert(std::find_if(begin(transitions), end(transitions), [&](std::unique_ptr<Transition>const& transIT)
			{
				return transIT.get() == transition;
			}) == end(transitions) && "Transition already registerd");

		auto it = begin(transitions);
		it = transitions.insert(it, std::unique_ptr<Transition>(transition));

		if (std::find_if(begin(states), end(states), [&](std::unique_ptr<State>& stateIT) {	return stateIT.get() == transition->SourceState; }) == end(states))
		{
			RegisterState(transition->SourceState);
		}

		if (std::find_if(begin(states), end(states), [&](std::unique_ptr<State>& stateIT) {	return stateIT.get() == transition->TargetState; }) == end(states))
		{
			RegisterState(transition->TargetState);
		}
	}
	void ActivateFsm(State* state)
	{
		assert(state != nullptr && "active state is a nullptr");
		assert(activeState == nullptr && "StateMachine already activated use a event to trigger transistion");
#ifdef STATE_DEBUG
		printf("Activated StateMachine with state: %s \n", typeid(state).name());
#endif
		state->OnStateEnter(nullptr);
		activeState = state;
	}
protected:
	virtual void OnStateRegister(State* state) {}

private:
	inline void RegisterState(State* state)
	{
		states.insert(begin(states), std::unique_ptr<State>(state));
		OnStateRegister(state);
	}
public:
	StateCallWrapper(Tick, float, deltaTime);
	StateCallWrapper(Render, Tmpl8::Surface*, surface);
	StateCallWrapper(OnMouseMove, Tmpl8::vec2, pos);
	StateCallWrapper(OnLeftClick, Tmpl8::vec2, pos);
};

#undef StateCallWrapper