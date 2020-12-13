#pragma once
#include <vcruntime_typeinfo.h>

#include "template.h"

class StateBase;

using namespace Tmpl8;
class TransitionBase
{
public:
	TransitionBase(StateBase* sourceState, StateBase* targetState, type_info* eventType)
	{
		this->SourceState = sourceState;
		this->TargetState = targetState;
		this->EventType = eventType;
	}

	virtual ~TransitionBase() = default;
protected:
	StateBase* SourceState;
	StateBase* TargetState;
	type_info* EventType;

	virtual bool TransitionGuard()
	{
		return true;
	}
	virtual void TransitionAction();

private:
	friend class FSM;

};

