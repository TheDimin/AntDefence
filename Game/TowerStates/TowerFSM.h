#pragma once
#include "..\..\Engine\FSM\Transition.h"
#include "TowerState.h"

#define TowerTransition Transition<TowerState>

class GameLevel;

class TowerFSM :
	public FSM<Transition<TowerState>, Event, TowerState>
{
public:
	TowerFSM(Tower* tower, GameLevel* lvl) :tower(tower), gLVL(lvl)
	{

	}
protected:
	void OnStateRegister(TowerState* state) override
	{
		state->tower = tower;
		state->gLVL = gLVL;
	}
	Tower* tower;
	GameLevel* gLVL;
};


