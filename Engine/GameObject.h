#pragma once
#include "EngineGlobal.h"
#include "../template.h"

class GameObject :ITickable, IRenderable
{
public:
	GameObject(Tmpl8::Sprite* sprite, Tmpl8::vec2 location, Tmpl8::vec2 size) :sprite(sprite), drawLocation(location), size(size)
	{
		centerLocation = Tmpl8::vec2(location.x + size.x * 0.5f, location.y + size.y * 0.5f);
	};

	virtual ~GameObject()
	{
		printf("Deconsturctor called \n");
	}
	friend class Level;

	virtual void OnLoad();
public:
	void Render(Tmpl8::Surface* surface) override
	{
		sprite->DrawScaled((int)drawLocation.x, (int)drawLocation.y, (int)size.x, (int)size.y, surface);
	}
	void Destroy();
private:
	virtual void SetLvl(Level* lvl)
	{
		this->lvl = lvl;
	}

public:
	Tmpl8::vec2 GetLocation() const { return centerLocation; }
	Tmpl8::vec2 GetDrawLocation() const { return drawLocation; }
	Tmpl8::vec2 GetSize() const { return size; }
	//Set objects location from RenderLocation
	void SetLocation(Tmpl8::vec2 loc)
	{
		centerLocation = Tmpl8::vec2(loc.x + size.x * 0.5f, loc.y + size.y * 0.5f);
		drawLocation = loc;
	}
	Tmpl8::vec2* GetSize() { return &size; }
public:
	void Tick(float deltaTime) override {};
	int rotation = 0;
	Tmpl8::Sprite* sprite;
	std::string Name = "GameObject";
	//std::vector<std::unique_ptr<Component>> Components;
protected:
	Level* lvl = nullptr;
	//DO NOT SET THESE , use the setter functions instead, thanks
	Tmpl8::vec2 size;
	Tmpl8::vec2 centerLocation;
	Tmpl8::vec2 drawLocation;


};
