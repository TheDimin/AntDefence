#pragma once
#include <../../Intake/template.h>

class EventBase;

using namespace Tmpl8;

class StateBase
{
public:
	void OnEnterState(EventBase* e);
};


