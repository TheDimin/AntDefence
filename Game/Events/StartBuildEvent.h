#pragma once
#include "../../Engine/FSM/Event.h"

struct TowerData;

class StartBuildEvent :
	public Event
{
public:
	StartBuildEvent(TowerData* tower) :towerData(tower) {};

	TowerData* towerData;
};

