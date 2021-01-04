#pragma once
#include "EngineGlobal.h"
#include "Component.h"
#include "../template.h"

class GameObject : IRenderable
{
protected:
	GameObject(Tmpl8::Sprite* sprite, Tmpl8::vec2 location, Tmpl8::vec2 size) :sprite(sprite), location(location), size(size) {};
	friend class Level;

	virtual void OnLoad();

	void Render(Tmpl8::Surface* surface) override
	{
		sprite->DrawScaled((int)location.x, (int)location.y, (int)size.x, (int)size.y, surface);
	}

public:
	Tmpl8::vec2* GetLocation() { return &location; }
	Tmpl8::vec2* GetSize() { return &size; }
public:

	Tmpl8::Sprite* sprite;
	std::string Name = "GameObject";
	std::vector<std::unique_ptr<Component>> Components;
protected:
	Tmpl8::vec2 location;
	Tmpl8::vec2 size;
};
