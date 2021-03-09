#pragma once
#include <iostream>

#include "GameState.h"
#include "../../Engine/FSM/Event.h"
#include "../../Engine/FSM/FSM.h"
#include "../../Engine/FSM/Transition.h"

#define GameTransition Transition<GameState>

class GameLevel;

class GameFSM : public FSM<GameTransition, Event, GameState>
{
public:
	GameFSM(GameLevel* level) :level(level)
	{
	}
	virtual ~GameFSM()
	{
		transitions.clear();
		states.clear();
		level = nullptr;

	};

protected:
	virtual void OnStateRegister(GameState* state) override
	{
		state->level = level;
	}


	GameLevel* level;
};

