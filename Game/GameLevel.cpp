#include "GameLevel.h"

#include <iostream>

#include "../Tower.h"
#include "../Engine/FSM/Transition.h"
#include "../Engine/UI/UIButton.h"
#include "GameStates/GameFSM.h"
#include "GameStates/PlayingState.h"
#include "GameStates/BuildingState.h"
#include "../Engine/FSM/FSM.h"
#include "Events/PlaceBuildingEvent.h"
#include "Events/StartBuildEvent.h"

GameLevel::GameLevel()
{
	gameState = std::make_unique<GameFSM>(this);


	auto* playingState = new PlayingState();
	auto* buildingState = new BuildingState();

	auto buildTestGuard = [this](Event* event) {
		GuardCastCheck(PlaceBuildingEvent, placeBuildingEvent);
		return CanPlaceTower(placeBuildingEvent->tile.x, placeBuildingEvent->tile.y, placeBuildingEvent->towerData);
	};

	auto* PlayingToBuildingTransition = new GameTransition(playingState, buildingState, DefaultGuardCastCheck(StartBuildEvent));
	auto* BuildingToBuildingTransition = new GameTransition(buildingState, buildingState, DefaultGuardCastCheck(StartBuildEvent));
	auto* BuildToPlayWithSuccesfullBuild = new GameTransition(buildingState, playingState,
		buildTestGuard, [this](Event* event)
		{
			printf("option a called \n");
			GuardCastCheck(PlaceBuildingEvent, placeBuildingEvent);
			TowerData* tData = placeBuildingEvent->towerData;
			SpendMoney(tData->price);
			RegisterObject(new Tower(tData, placeBuildingEvent->tile, placeBuildingEvent->location, vec2(CalculateTileWidth(), CalculateTileHeight())));
			return true;
		});
	auto* BuildToPlayWithFailedBuild = new GameTransition(buildingState, playingState, [buildTestGuard](Event* event)
		{
			return !buildTestGuard(event);
		});

	gameState->RegisterTransition(PlayingToBuildingTransition);
	gameState->RegisterTransition(BuildingToBuildingTransition);
	gameState->RegisterTransition(BuildToPlayWithSuccesfullBuild);
	gameState->RegisterTransition(BuildToPlayWithFailedBuild);
	gameState->ActivateFsm(playingState);
}

void GameLevel::RegisterObject(GameObject* obj)
{
	Level::RegisterObject(obj);
	Tower* tower = reinterpret_cast<Tower*>(obj);
	if (tower != nullptr)
	{
		PlacedTowers.insert(begin(PlacedTowers), std::pair<Tmpl8::vec2, GameObject*>(tower->tile, obj));
	}
}

uint GameLevel::GetMoney() const
{
	return Money;
}

bool GameLevel::SpendMoney(uint amount)
{
	if (amount > Money) return false;

	Money -= amount;
	MoneyText = "Money: " + std::to_string(Money);
	return true;
}

bool GameLevel::CanPlaceTower(float x, float y, TowerData* tower)
{
	auto* p = GetMapSprite((int)x, (int)y);

	if (p == nullptr)
		return false;

	if (!p->canBuild)
		return false;

	vec2 tVec2 = vec2(x, y);


	for (auto element : PlacedTowers)
	{
		if (element.first == tVec2) return false;
	}
	//if (p->PlacedTowerAtLocation)
	//	return false;

	return true;
}

void GameLevel::CreateUI(UiContainer* UI)
{
	StyleInfo style = StyleInfo{
	0x0000000,
	0xFFFFFFFF,
	0x11111,
	0x00FFFF
	};

	for (int i = 0; i < 4; ++i)
	{
		if (mapStyle->towers.size() <= static_cast<unsigned>(i))
			break;

		TowerData* tower = mapStyle->towers[i].get();

		style.Image = tower->asset;

		UI->Button(45 + (90 * i), 60, 40, 40)
			->SetStyle(style)
			->SetOnClick([this, tower] { gameState->InvokeEvent(new StartBuildEvent(tower)); })
			->SetIsActiveLambda([this, tower] { return Money >= static_cast<uint>(tower->price); });

		UI->Text(45 + (90 * i), 120, tower->displayName);
		UI->Text(45 + (90 * i), 140, "Cost: " + std::to_string(tower->price));
	}

	UI->Text(500, 20, &MoneyText);
}
