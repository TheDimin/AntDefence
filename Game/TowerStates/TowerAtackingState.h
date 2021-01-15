#pragma once
#include "TowerState.h"
#include "../Mob.h"

class TowerAtackingState :
	public TowerState
{
public:
	void OnStateEnter(Event* e) override;
	void OnStateExit(Event* newEvent) override;
	void Tick(float deltaTime) override;
	void OnMouseDown(Tmpl8::vec2& mousePos) override;
	void OnMouseMove(Tmpl8::vec2& mousePos) override;
	void Render(Tmpl8::Surface* surface) override;

	Mob* TargetMob;
	MobData* mobData; //When the mob gets killed, we still need access to the mobData so we ref it aswell
	bool attacked = false;
};

