#pragma once
#include "FSM.h"
#include "../EngineGlobal.h"



namespace Tmpl8 {
	class Surface;
	class vec2;
}

class Event;

class State : ITickable, IRenderable
{
public:
	virtual void OnStateEnter(Event* e) = 0;
	virtual void OnStateExit(Event* newEvent) = 0;


	virtual void Render(::Tmpl8::Surface* surface) override = 0;
	void Tick(float deltaTime) override {};
	virtual void OnLeftClick(Tmpl8::vec2& mousePos) = 0;
	virtual void OnMouseMove(Tmpl8::vec2& mousePos) = 0;
};