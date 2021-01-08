#pragma once
#include "../../Engine/FSM/State.h"

class GameLevel;
class Tower;

class TowerState :
	public State
{
	friend class TowerFSM;
protected:
	Tower* tower;
	GameLevel* gLVL;
	float TickCooldown = 0;
};

