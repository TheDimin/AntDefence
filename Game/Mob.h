#pragma once
#include "Style.h"
#include "../Engine/GameObject.h"

struct MobData;

class Mob :
	public GameObject
{
public:
	Mob(MobData* mobData, std::vector<Tmpl8::vec2>* route, const Tmpl8::vec2& size);
	~Mob();
	bool TakeDamage(int& amount);
public:
	void Tick(float deltaTime) override;


	void Render(Tmpl8::Surface* surface) override;
public:
	MobData* mobData = nullptr;
	std::vector<Tmpl8::vec2>* route;
	uint currentRouteIndex = 0;
	Tmpl8::vec2 dir;
	Tmpl8::vec2 target;
	int health = 0;
	int maxHealth = 0;
	//std::string healthText = "HP:";
	int currentFrame = 0;
	float frameTime = 0;
};

