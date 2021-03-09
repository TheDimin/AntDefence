#include "Mob.h"
#include "GameLevel.h"
#include "../Engine/Level.h"

Mob::Mob(MobData* mobData, std::vector<Tmpl8::vec2>* route, const Tmpl8::vec2& size) :
	GameObject(mobData->asset.get(), Tmpl8::vec2(0, 0), size), route(route),
	mobData(mobData)
{
	SetLocation(route->at(0) * size);
	target = route->at(1) * size;
	dir = Tmpl8::vec2::normalize(target - GetDrawLocation());
	health = (int)mobData->FindStat(0)->amount;

	//healthText = "HP: " + std::to_string(health);
	maxHealth = health;

}

Mob::~Mob()
{
	printf("Dconstructor called \n");
	GameLevel* glvl = dynamic_cast<GameLevel*>(lvl);
	auto element = std::find_if(
		begin(glvl->activeMobs),
		end(glvl->activeMobs),
		[this](Mob* mob) {return mob == this; });
	if (element != end(glvl->activeMobs))
	{
		glvl->activeMobs.erase(element);
		glvl->activeMobCount--;
	}
}

bool Mob::TakeDamage(int& Amount)
{
	if (this == nullptr) return false;
	health -= Amount;
	if (health <= 0)
	{
		this->Destroy();
		return true;
	}
	//healthText = "HP: " + std::to_string(health);
	return false;
}

void Mob::Tick(float deltaTime)
{
	frameTime -= deltaTime;
	if (frameTime < 0)
	{
		frameTime = 400;
		currentFrame++;
		if (currentFrame == 3)
			currentFrame = 0;
	}

	vec2 newloc = GetDrawLocation() + dir * mobData->speed * 0.01f * deltaTime;
	SetLocation(newloc);

	if ((newloc - target).length() < mobData->speed * 0.01f * deltaTime * 2)
	{
		newloc = target;
		SetLocation(target);
		currentRouteIndex++;
		if (route->size() > currentRouteIndex) {
			target = route->at(currentRouteIndex) * size;
			dir = Tmpl8::vec2::normalize((target - newloc) + vec2(1, 1));
			return;
		}
		GameLevel* glvl = dynamic_cast<GameLevel*>(lvl);
		glvl->TakeDamage(mobData->damage);
		Destroy();
	}

	//Direction to sprite index
	if (round(dir.x) == 1)
	{
		rotation = 1;
	}
	else if (round(dir.x) == -1)
	{
		rotation = 3;
	}
	else if (round(dir.y) == 1)
	{
		rotation = 2;
	}
	else
	{
		rotation = 0;
	}

}


void Mob::Render(Tmpl8::Surface* surface)
{
	sprite->SetFrame(rotation * 3 + currentFrame);
	GameObject::Render(surface);

	float hpFactor = -1 * ((float)health / (float)maxHealth) + 1;
	surface->Bar((int)GetDrawLocation().x + 10, (int)GetDrawLocation().y - 10, (int)GetDrawLocation().x + (int)size.x - 10, (int)GetDrawLocation().y - 5, 0x008000);

	int x = (int)ceil((size.x - 15) * hpFactor);
	surface->Bar((int)GetDrawLocation().x + (int)size.x - 9 - x, (int)GetDrawLocation().y - 10, (int)GetDrawLocation().x + (int)size.x - 10, (int)GetDrawLocation().y - 5, 0xFF0000);
}
