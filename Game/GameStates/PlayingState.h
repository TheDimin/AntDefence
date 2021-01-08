#pragma once
#include "GameState.h"

class PlayingState : public GameState
{
public:
	void OnStateEnter(Event* e) override;
	void OnStateExit(Event* newEvent) override;
	void OnMouseDown(Tmpl8::vec2& mousePos) override;
	void OnMouseMove(Tmpl8::vec2& mousePos) override;
	void Tick(float deltaTime) override;
	void Render(Tmpl8::Surface* surface) override;
};
