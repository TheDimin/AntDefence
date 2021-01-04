#pragma once

namespace Tmpl8 {
	class Surface;
	class vec2;
}

class Event;

class State
{
public:
	virtual void OnStateEnter(Event* e) = 0;

	virtual void OnStateExit(Event* newEvent) = 0;
	virtual void Update(float deltaTime) = 0; //TODO: add deltaTime ?

	virtual void OnMouseDown(Tmpl8::vec2& mousePos) = 0;
	virtual void OnMouseMove(Tmpl8::vec2& mousePos) = 0;
	virtual void Draw(Tmpl8::Surface* surface) = 0;
};