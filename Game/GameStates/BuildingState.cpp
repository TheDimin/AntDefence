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

void BuildingState::Update(float deltaTime)
{

}

void BuildingState::OnMouseDown(Tmpl8::vec2& mousePos)
{
	float w = floor((mousePos.x) / level->CalculateTileWidth());
	float h = floor((mousePos.y) / level->CalculateTileHeight());

	level->gameState->InvokeEvent(new PlaceBuildingEvent(vec2(w, h), vec2(((float)level->CalculateTileWidth() * w), level->CalculateTileHeight() * h), vec2(level->CalculateTileWidth(), level->CalculateTileHeight()), SelectedBuildTower));
}

void BuildingState::Draw(Tmpl8::Surface* surface)
{
	float drawX = floor((mousePos.x) / level->CalculateTileWidth());
	float drawY = floor((mousePos.y) / level->CalculateTileHeight());
	if (!level->CanPlaceTower(drawX, drawY, SelectedBuildTower))
		SelectedBuildTower->asset->DrawScaled((int)level->CalculateTileWidth() * drawX, (int)level->CalculateTileHeight() * drawY, (int)level->CalculateTileWidth(), (int)level->CalculateTileHeight(), 0xb30000, surface);
	else
		SelectedBuildTower->asset->DrawScaled((int)level->CalculateTileWidth() * drawX, (int)level->CalculateTileHeight() * drawY, (int)floor(level->CalculateTileWidth()), (int)floor(level->CalculateTileHeight()), surface);
}

void BuildingState::OnMouseMove(Tmpl8::vec2& mousePos)
{
	int x, y = 0;
	SDL_GetMouseState(&x, &y);
	this->mousePos = Tmpl8::vec2((float)x, (float)y);//set current mouse pos

	//this->mousePos = mousePos;
}