#pragma once
#include <functional>

#define TransitionBase Transition<State>

class State;
class Event;

template<typename State>
class Transition
{
public:
	Transition(State* sourceState, State* targetState, const std::function<bool(Event*)>& guardLambda,
		const std::function<void(Event*)>& actionLambda = nullptr)
		: SourceState(sourceState),
		TargetState(targetState),
		GuardLambda(guardLambda),
		ActionLambda(actionLambda)
	{
	}

	virtual ~Transition() = default;
	State* SourceState;
	State* TargetState;

	std::function<bool(Event*)> GuardLambda;
	std::function<void(Event*)> ActionLambda;

	virtual bool TransitionGuard(Event* event)
	{
		return GuardLambda(event);
	}

	virtual void TransitionAction(Event* event)
	{
		if (ActionLambda != nullptr)
			ActionLambda(event);
	}
};