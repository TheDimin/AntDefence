#pragma once
#include "TowerState.h"

class TowerIdleState :
	public TowerState
{
public:
	void OnStateEnter(Event* e) override;
	void OnStateExit(Event* newEvent) override;
	void Tick(float deltaTime) override;
	void OnLeftClick(Tmpl8::vec2& mousePos) override;
	void OnMouseMove(Tmpl8::vec2& mousePos) override;
	void Render(Tmpl8::Surface* surface) override;
};

