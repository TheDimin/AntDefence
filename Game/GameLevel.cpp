#include "GameLevel.h"

#include <iostream>


#include "Mob.h"
#include "Tower.h"
#include "../Engine/FSM/Transition.h"
#include "../Engine/UI/UIButton.h"
#include "GameStates/GameFSM.h"
#include "GameStates/PlayingState.h"
#include "GameStates/BuildingState.h"
#include "../Engine/FSM/FSM.h"
#include "../Engine/UI/UIText.h"
#include "Events/PlaceBuildingEvent.h"
#include "Events/StartBuildEvent.h"


#define MapJsonData(valueName,source) json.at(#valueName).get_to(source.valueName);

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
			GuardCastCheck(PlaceBuildingEvent, placeBuildingEvent);
			TowerData* tData = placeBuildingEvent->towerData;
			SpendMoney(tData->price);
			Tower* tower = new Tower(tData, placeBuildingEvent->tile, placeBuildingEvent->location, vec2(CalculateTileWidth(), CalculateTileHeight()));
			RegisterObject(reinterpret_cast<GameObject*&>(tower));
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
	Tower* tower = dynamic_cast<Tower*>(obj);
	if (tower != nullptr)
	{
		placedTowers.insert(begin(placedTowers), std::pair<Tmpl8::vec2, GameObject*>(tower->tile, obj));
		return;
	}

	Mob* mob = dynamic_cast<Mob*>(obj);
	if (mob != nullptr)
	{
		activeMobs.insert(begin(activeMobs), mob);
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

void GameLevel::AddMoney(uint amount)
{
	Money += amount;
	MoneyText = "Money: " + std::to_string(Money);
}

bool GameLevel::TakeDamage(int amount)
{
	if (amount > Health) return true;
	Health -= amount;
	HealthText = "Health: " + std::to_string(Health);

	return false;
}

bool GameLevel::CanPlaceTower(float x, float y, TowerData* tower)
{
	auto* p = GetMapSprite((int)x, (int)y);

	if (p == nullptr)
		return false;

	if (!p->canBuild)
		return false;

	vec2 tVec2 = vec2(x, y);


	for (auto element : placedTowers)
	{
		if (element.first == tVec2) return false;
	}
	//if (p->PlacedTowerAtLocation)
	//	return false;

	return true;
}

void GameLevel::StartNextWave()
{
	if (waveInstance != nullptr)
	{
		printf("Attempted to start wave while one is already active");
		return;
	}

	activeMobs.clear();
	waveIndex++;
	waveInstance = mapStyle->GetWave(waveIndex);
}

void GameLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);
	gameState->Tick(deltaTime);

	if (waveInstance != nullptr)
	{
		if (waveStep >= (int)waveInstance->waves.size())
		{
			if (activeMobCount > 0)return;
			waveInstance = nullptr;
			waveTimer = 0;
			waveStep = 0;
			return;
		}


		waveTimer -= deltaTime;
		if (waveTimer > 0)
			return;

		//TODO SPAWN MOB
		float w = CalculateTileWidth();
		float h = CalculateTileHeight();

		spawnedOfCurrentMobType++;
		waveTimer = w / waveInstance->waves[waveStep].mob->speed * 100;

		activeMobCount++;
		Mob* mob = new Mob(waveInstance->waves[waveStep].mob, &route, vec2(w, h));
		RegisterObject(reinterpret_cast<GameObject*&>(mob));

		if (waveInstance->waves[waveStep].amount == spawnedOfCurrentMobType)
		{
			waveStep++;
			spawnedOfCurrentMobType = 0;
		}
	}
}

Tmpl8::Sprite* dollarSign = new Tmpl8::Sprite(new Surface("assets/DollarSign.png"), 1);


void GameLevel::CreateUI(UiContainer* UI)
{
	StyleInfo style = StyleInfo{
	0x0000000,
	0xFFFFFFFF,
	0x11111,
	0x00FFFF
	};

	UiContainer* DefaultUI = UI->Container(0, 0, (int)UI->getScale().x - 250, (int)UI->getScale().y);

	const int ShopItemsOffset = 100;
	for (int i = 0; i < 4; ++i)
	{
		if (mapStyle->towers.size() <= static_cast<unsigned>(i))
			break;

		TowerData* tower = mapStyle->towers[i].get();

		DefaultUI->Text(ShopItemsOffset - 15 + (150 * i), 132, 3, std::to_string(tower->price))
			->SetTextCentert(false);
		style.Image = dollarSign;
		DefaultUI->Button(ShopItemsOffset - 30 + (150 * i), 140, 12, 12)->SetStyle(style);

		style.Image = tower->asset.get();
		DefaultUI->Button(ShopItemsOffset + (150 * i), 65, 60, 60)
			->SetStyle(style)
			->SetOnClick([this, tower]
				{
					gameState->InvokeEvent(new StartBuildEvent(tower));
				})
			->SetIsActiveLambda([this, tower]
				{
					return Money >= static_cast<uint>(tower->price);
				});

				//DefaultUI->Text(ShopItemsOffset + (90 * i), 120, 2, &tower->displayName);
	}
	DefaultUI->SetIsActiveLambda([this]()
		{
			return dynamic_cast<BuildingState*>(gameState->GetState()) != nullptr;
		});

	// MAIN UI
	UI->Button(UI->GetWidth() - 100, UI->GetHeight() - 50, 70, 15)
		->SetIsHiddenLambda([this]() {return waveInstance != nullptr; })
		->SetOnClick([this]() {StartNextWave(); })
		->SetText(&StartNextWaveText);

	UI->Text(UI->GetWidth() - 170, 20, 2, &MoneyText)->SetTextCentert(false);
	UI->Text(UI->GetWidth() - 170, 40, 2, &HealthText)->SetTextCentert(false);
}

void from_json(const nlohmann::json& json, GameLevel& lvl)
{
	json.get_to<Level>(lvl);
	MapJsonData(Money, lvl);
	MapJsonData(Health, lvl);
	lvl.MoneyText = "MONEY: " + std::to_string(lvl.Money);
	lvl.HealthText = "Health: " + std::to_string(lvl.Health);

	auto startPos = json.at("startPos").get<std::vector<int>>();

	auto mapPoints = json["map"].get<	std::vector<std::vector<int>>>();

	vec2 CurrentLocation = vec2((float)startPos[0], (float)startPos[1]);

	std::vector<vec2> route = std::vector<vec2>();

	MapSprite* mapSprite = lvl.GetMapSprite(startPos[0], startPos[1]);
	if (!mapSprite->canWalk)
	{
		assert("START POS IS NOT WALKABLE");
	}

	route.insert(begin(route), CurrentLocation);

	while (true)
	{
		bool FoundNextPos = false;
		for (int x = -1; x < 2; x += 1)
		{
			int finalX = (int)CurrentLocation.x + x;
			if (finalX < 0 && finalX < (int)mapPoints[0].size())
				continue;

			for (int y = -1; y < 2; y += 1)
			{
				if (x == 1 && y == 1)
					continue;

				//TODO some forloop math should allow us to not even try and waste a itteration on this corner check bs
				if (x == -1 && y == -1)
					continue;
				if (x == 1 && y == -1)
					continue;
				if (x == -1 && y == 1)
					continue;
				if (x == 1 && y == 1)
					continue;

				int finalY = (int)CurrentLocation.y + y;
				if (finalY < 0 && finalY < (int)mapPoints.size())
					continue;

				if (std::find_if(begin(route), end(route), [finalX, finalY](vec2 elem) {return elem.x == finalX && elem.y == finalY; }) != end(route))
					continue;

				MapSprite* mapSprite = lvl.GetMapSprite(finalX, finalY);
				if (mapSprite != nullptr && mapSprite->canWalk)
				{
					CurrentLocation = vec2((float)finalX, (float)finalY);
					route.insert(end(route), CurrentLocation);
					FoundNextPos = true;
					break;
				}
			}
			if (FoundNextPos)
				break;
		}

		if (!FoundNextPos)
		{
			//assume we reached the end
#ifdef PATH_DEBUG
			printf("Path generation reached a endpoint \n");
#endif

			break;
		}

	}
	lvl.route = route;

#ifdef PATH_DEBUG
	//Path debug info
	float h = lvl.CalculateTileHeight();
	float w = lvl.CalculateTileWidth();
	vec2 start = route[0];

	for (int i = 1; i < route.size(); ++i)
	{
		vec2 end = route[i];

		lvl.surface->Line(start.x * w + w * 0.5f, start.y * h + h * 0.5f, end.x * w + w * 0.5f, end.y * h + h * 0.5f, 0xff00000);
		start = end;
	}
#endif
}


#undef MapJsonData