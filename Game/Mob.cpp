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

	//uiContainer = std::make_unique<UiContainer>(&location, 50, 10);
	healthText = "HP: " + std::to_string(health);
	//uiContainer->Text(0, 5, &healthText);

}
Mob::~Mob()
{
	GameLevel* glvl = dynamic_cast<GameLevel*>(lvl);
	glvl->activeMobCount--;
	glvl->activeMobs.erase(std::remove(begin(glvl->activeMobs), end(glvl->activeMobs), this), end(glvl->activeMobs));
}

bool Mob::TakeDamage(int& Amount)
{
	health -= Amount;
	if (health <= 0)
	{
		this->Destroy();
		return true;
	}
	healthText = "HP: " + std::to_string(health);
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
			dir = Tmpl8::vec2::normalize(target - newloc);
			return;
		}
		GameLevel* glvl = dynamic_cast<GameLevel*>(lvl);
		glvl->TakeDamage(mobData->damage);
		Destroy();
	}

	if ((int)dir.x == 1)
	{
		rotation = 1;
	}
	else if ((int)dir.x == -1)
	{
		rotation = 3;
	}
	else if ((int)dir.y == 1)
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

	//sprite->DrawScaled((int)drawLocation.x, (int)drawLocation.y, (int)size.x, (int)size.x, surface);
}
