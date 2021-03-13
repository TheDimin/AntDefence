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
	OnMouseMove(mousePos);
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

void BuildingState::OnLeftClick(Tmpl8::vec2& _)
{
	level->gameState->InvokeEvent(new PlaceBuildingEvent(drawIndex, drawPos, vec2(level->CalculateTileWidth(), level->CalculateTileHeight()), SelectedBuildTower));
}

void BuildingState::Render(Tmpl8::Surface* surface)
{


	int width = (int)floor(level->CalculateTileWidth());
	int height = (int)floor(level->CalculateTileHeight());

	int indexX = (int)floor((mousePos.x) / level->CalculateTileWidth());
	int indexY = (int)floor((mousePos.y) / level->CalculateTileHeight());

	bool canPlaceTower = level->CanPlaceTower((float)indexX, (float)indexY, SelectedBuildTower);

	float w = level->CalculateTileWidth() * (SelectedBuildTower->range + 2);
	float h = level->CalculateTileHeight() * (SelectedBuildTower->range + 2);

	circleSprite->BlendScaled(
		(int)(drawPos.x - (w * 0.5f - level->CalculateTileWidth() * .5f)),
		(int)(drawPos.y - (h * 0.5f - level->CalculateTileHeight() * .5f)),
		(int)w, (int)h, 0x383838, surface);

	SelectedBuildTower->asset->SetFrame(0);

	if (canPlaceTower)
	{
		SelectedBuildTower->asset->DrawScaled((int)drawPos.x, (int)drawPos.y, width, height, surface);
		SelectedBuildTower->asset->SetFrame(1);
		SelectedBuildTower->asset->DrawScaled((int)drawPos.x - 5, (int)drawPos.y - 10, width, height, surface, 0);
	}
	else
	{
		SelectedBuildTower->asset->DrawScaled((int)drawPos.x, (int)drawPos.y, width, height, 0xff0000, surface);
		SelectedBuildTower->asset->SetFrame(1);
		SelectedBuildTower->asset->DrawScaled((int)drawPos.x - 5, (int)drawPos.y - 10, width, height, 0xff0000, surface, 0);
	}

}

void BuildingState::OnMouseMove(Tmpl8::vec2& _)
{
	int x, y = 0;
	SDL_GetMouseState(&x, &y);
	this->mousePos = Tmpl8::vec2((float)x, (float)y);//set current mouse pos
	int drawX = (int)(level->CalculateTileWidth() * floor((x) / level->CalculateTileWidth()));
	int drawY = (int)(level->CalculateTileHeight() * floor((y) / level->CalculateTileHeight()));

	this->drawIndex = { x / level->CalculateTileWidth(),(y) / level->CalculateTileHeight() };
	this->drawPos = vec2(drawX, drawY);
	//this->mousePos = mousePos;
}