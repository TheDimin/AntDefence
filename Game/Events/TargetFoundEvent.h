#pragma once
#include "../../Engine/FSM/Event.h"

class Mob;

class TargetFoundEvent :
	public Event
{
public:
	TargetFoundEvent(Mob* targetMob) :mob(targetMob) {}
	~TargetFoundEvent() {}
	
	Mob* mob;
};

