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

	std::cout << "[BuildingState]: OnEnter" << std::endl;
	SelectedBuildTower = reinterpret_cast<StartBuildEvent*>(e)->towerData;
}

void BuildingState::OnStateExit(Event* newEvent)
{
	SelectedBuildTower = nullptr;
	std::cout << "[BuildingState]: OnStateExit" << std::endl;
}

void BuildingState::Tick(float deltaTime)
{
	std::cout << "[BuildingState]: Tick" << std::endl;
}

void BuildingState::OnMouseDown(Tmpl8::vec2& mousePos)
{
	float w = floor((mousePos.x) / level->CalculateTileWidth());
	float h = floor((mousePos.y) / level->CalculateTileHeight());

	level->gameState->InvokeEvent(new PlaceBuildingEvent(vec2(w, h), vec2(((float)level->CalculateTileWidth() * w), level->CalculateTileHeight() * h), vec2(level->CalculateTileWidth(), level->CalculateTileHeight()), SelectedBuildTower));
}

void BuildingState::Render(Tmpl8::Surface* surface)
{
	float drawX = floor((mousePos.x) / level->CalculateTileWidth());
	float drawY = floor((mousePos.y) / level->CalculateTileHeight());
	bool canPlaceTower = level->CanPlaceTower(drawX, drawY, SelectedBuildTower);
	drawX = level->CalculateTileWidth() * drawX;
	drawY = level->CalculateTileHeight() * drawY;

	float w = level->CalculateTileWidth() * (SelectedBuildTower->range + 2);
	float h = level->CalculateTileHeight() * (SelectedBuildTower->range + 2);

	circleSprite->BlendScaled(
		(int)(drawX - (w * 0.5f - level->CalculateTileWidth() * .5f)),
		(int)(drawY - (h * 0.5f - level->CalculateTileHeight() * .5f)),
		(int)w, (int)h, 0x383838, surface);

	if (!canPlaceTower)
		SelectedBuildTower->asset->DrawScaled((int)drawX, (int)drawY, (int)level->CalculateTileWidth(), (int)level->CalculateTileHeight(), 0xb30000, surface);
	else
		SelectedBuildTower->asset->DrawScaled((int)drawX, (int)drawY, (int)floor(level->CalculateTileWidth()), (int)floor(level->CalculateTileHeight()), surface);
}

void BuildingState::OnMouseMove(Tmpl8::vec2& mousePos)
{
	int x, y = 0;
	SDL_GetMouseState(&x, &y);
	this->mousePos = Tmpl8::vec2((float)x, (float)y);//set current mouse pos

	//this->mousePos = mousePos;
}