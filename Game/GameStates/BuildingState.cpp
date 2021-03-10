#include "BuildingState.h"
#include "../../Engine/FSM/Event.h"
#include <iostream>
#include <ostream>
#include <SDL_mouse.h>

#include "../GameLevel.h"
#include "../Style.h"
#include "../../template.h"
#include "../../Engine/EngineGlobal.h"
#include "../Events/PlaceBuildingEvent.h"

#include "../Events/StartBuildEvent.h"


BuildingState::BuildingState()
{
	circleSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/Circle.png"), 1);
}

BuildingState::~BuildingState()
{
	delete circleSprite;
}

void BuildingState::OnStateEnter(Event* e)
{
	int x, y = 0;
	SDL_GetMouseState(&x, &y);
	mousePos = Tmpl8::vec2((float)x, (float)y);//set current mouse pos

#ifdef STATE_DEBUG
	std::cout << "[BuildingState]: OnEnter" << std::endl;
#endif
	SelectedBuildTower = reinterpret_cast<StartBuildEvent*>(e)->towerData;
}

void BuildingState::OnStateExit(Event* newEvent)
{
	SelectedBuildTower = nullptr;
#ifdef  STATE_DEBUG
	std::cout << "[BuildingState]: OnStateExit" << std::endl;
#endif
}

void BuildingState::Tick(float deltaTime)
{
	//std::cout << "[BuildingState]: Tick" << std::endl;
}

void BuildingState::OnLeftClick(Tmpl8::vec2& mousePos)
{
	float w = floor((mousePos.x) / level->CalculateTileWidth());
	float h = floor((mousePos.y) / level->CalculateTileHeight());

	level->gameState->InvokeEvent(new PlaceBuildingEvent(vec2(w, h), vec2(((float)level->CalculateTileWidth() * w), level->CalculateTileHeight() * h), vec2(level->CalculateTileWidth(), level->CalculateTileHeight()), SelectedBuildTower));
}

void BuildingState::Render(Tmpl8::Surface* surface)
{
	int drawX = (int)floor((mousePos.x) / level->CalculateTileWidth());
	int drawY = (int)floor((mousePos.y) / level->CalculateTileHeight());

	int width = (int)floor(level->CalculateTileWidth());
	int height = (int)floor(level->CalculateTileHeight());

	bool canPlaceTower = level->CanPlaceTower(drawX, drawY, SelectedBuildTower);
	drawX = level->CalculateTileWidth() * drawX;
	drawY = level->CalculateTileHeight() * drawY;

	float w = level->CalculateTileWidth() * (SelectedBuildTower->range + 2);
	float h = level->CalculateTileHeight() * (SelectedBuildTower->range + 2);

	circleSprite->BlendScaled(
		(int)(drawX - (w * 0.5f - level->CalculateTileWidth() * .5f)),
		(int)(drawY - (h * 0.5f - level->CalculateTileHeight() * .5f)),
		(int)w, (int)h, 0x383838, surface);

	for (int i = 0; i < 2; ++i)
	{
		SelectedBuildTower->asset->SetFrame(i);

		canPlaceTower ?
			SelectedBuildTower->asset->DrawScaled(drawX, drawY, width, height, surface) :
			SelectedBuildTower->asset->DrawScaled(drawX, drawY, width, height, 0xff0000, surface);
	}
}

void BuildingState::OnMouseMove(Tmpl8::vec2& mousePos)
{
	int x, y = 0;
	SDL_GetMouseState(&x, &y);
	this->mousePos = Tmpl8::vec2((float)x, (float)y);//set current mouse pos

	//this->mousePos = mousePos;
}