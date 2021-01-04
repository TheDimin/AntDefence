#pragma once
#include "Engine/FSM/State.h"

class GameLevel;

class GameState :
	public State
{
	friend class GameFSM;
protected:
	GameLevel* level;
};

