#include "GameLevel.h"

#include <iostream>
#include "Mob.h"
#include "Tower.h"
#include "../game.h"
#include "../Engine/LevelHelper.h"
#include "../Engine/FSM/Transition.h"
#include "../Engine/UI/UIButton.h"
#include "GameStates/GameFSM.h"
#include "GameStates/PlayingState.h"
#include "GameStates/BuildingState.h"
#include "../Engine/FSM/FSM.h"
#include "../Engine/UI/UIModal.h"
#include "../Engine/UI/UIText.h"
#include "Events/PlaceBuildingEvent.h"
#include "Events/StartBuildEvent.h"


#define MapJsonData(valueName,source) json.at(#valueName).get_to(source.valueName);

#define GameStateWrapperInjection(Function,ParamType,ParamName)	\
	void GameLevel::Function(ParamType ParamName) {				\
		gameState->Function(ParamName);							\
		if(activeModal == nullptr)								\
		activeModal->Function(ParamName)						\
		Level::Function(ParamName);								\
	}															\




const Tmpl8::Sprite* dollarSign = new Tmpl8::Sprite(new Surface("assets/DollarSign.png"), 1);

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

GameLevel::~GameLevel()
{
	placedTowers.clear();
	activeMobs.clear();
	route.clear();
	//delete waveInstance;
	mapStyle.reset();
	surface.reset();
	objects.clear();
	mapTiles.clear();
	ToDeleteObjects.clear();
	uiContainer.reset();
	gameState.reset();
	if (activeModal != nullptr) // justs to be sure we destroy it, should be handeld when we press a button
	{
		//	delete activeModal;
		activeModal = nullptr;
	}

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
	Health -= amount;
	HealthText = "Health: " + std::to_string(Health);

	if (amount >= Health)
	{
		activeModal = UIModal::Get(surface.get());
		activeModal->SetMessage("You died!");
		activeModal->SetAcceptText(" Restart ");
		activeModal->SetOnAccept([this]() {game->SwitchLevel<GameLevel>(name); });

		activeModal->SetCancelText("   Quit   ");
		activeModal->SetOnCancel([this]() {game->SwitchLevel<MainMenu>(""); });

		activeModal->SetOnOptional(nullptr);
		return true;
	}

	return false;
}

bool GameLevel::IsPaused() const
{
	return Paused || activeModal != nullptr;
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
	CurrentWaveText = "Wave: " + std::to_string(waveIndex + 1);
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
			if (waveIndex + 1 >= (int)mapStyle->waves.size())
			{
				activeModal = UIModal::Get(surface.get());
				activeModal->SetMessage("You won!");
				activeModal->SetCancelText("   Quit   ");
				activeModal->SetOnCancel([this]()
					{
						game->SwitchLevel<MainMenu>("");
					});

				activeModal->SetAcceptText(" Restart ");
				activeModal->SetOnAccept([this]() {
					game->SwitchLevel<GameLevel>(name);
					});

				activeModal->SetOnOptional(nullptr);
			}
			return;
		}


		waveTimer -= deltaTime;
		if (waveTimer > 0)
			return;

		//TODO SPAWN MOB
		float w = CalculateTileWidth();
		float h = CalculateTileHeight();

		spawnedOfCurrentMobType++;
		waveTimer = waveInstance->waves[waveStep].interval * 100;

		activeMobCount++;
		Mob* mob = new Mob(waveInstance->waves[waveStep].mob, &route, vec2(w, h));
		RegisterObject(reinterpret_cast<GameObject*>(mob));

		if (waveInstance->waves[waveStep].amount == spawnedOfCurrentMobType)
		{
			waveStep++;
			spawnedOfCurrentMobType = 0;
		}
	}
}

void GameLevel::Render(Surface* Surface)
{
	Level::Render(Surface);
	gameState->Render(Surface);

	if (activeModal != nullptr)
		activeModal->Render(Surface);
}

void GameLevel::OnMouseMove(vec2 mousePos)
{
	if (activeModal != nullptr)
		activeModal->OnMouseMove(mousePos);

	if (IsPaused())
		return;

	gameState->OnMouseMove(mousePos);
	Level::OnMouseMove(mousePos);
}

void GameLevel::OnLeftClick(vec2 mousePos)
{
	if (activeModal != nullptr)
		activeModal->OnLeftClick();

	if (IsPaused())
		return;

	gameState->OnLeftClick(mousePos);
	Level::OnLeftClick(mousePos);
}

void GameLevel::CreateUI(UiContainer* UI)
{
	StyleInfo style = StyleInfo{
	0x0000000,
	0x181818,
	0x11111,
	0x383838
	};

	// Container for bottom part of the screen
	UiContainer* DefaultUI = UI->Container(0, 0, (int)UI->getScale().x - 250, (int)UI->getScale().y);
	
	const int ShopItemsOffset = 100;
	for (int i = 0; i < 4; ++i) //Hardcoded max of 4 towers
	{
		if (mapStyle->towers.size() <= static_cast<unsigned>(i)) //less then 4 towers ? done creating ui elements
			break;

		TowerData* tower = mapStyle->towers[i].get();
		//Price text
		DefaultUI->Text(ShopItemsOffset - 15 + (150 * i), 132, 3, std::to_string(tower->price))->SetTextCentert(false);
		
		style.Image = const_cast<Sprite*>(dollarSign);
		DefaultUI->Button(ShopItemsOffset - 30 + (150 * i), 140, 12, 12)->SetStyle(style);

		style.Image = tower->asset.get();
		style.SpriteIndex = 4;
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
		->SetIsHiddenLambda([this]()
		{
			return waveInstance != nullptr;
		})
		->SetOnClick([this]()
		{
			StartNextWave();
		})
		->SetText(&StartNextWaveText);

	UI->Text(UI->GetWidth() - 170, 20, 2, &MoneyText)->SetTextCentert(false);
	UI->Text(UI->GetWidth() - 170, 40, 2, &HealthText)->SetTextCentert(false);
	UI->Text(UI->GetWidth() - 170, 60, 2, &CurrentWaveText)->SetTextCentert(false);
}

void GameLevel::OnKeyDown(int key)
{
	if (key == 41)
	{
		if (activeModal != nullptr)
		{
			Paused = false;
			activeModal = nullptr;
			return;
		}

		activeModal = UIModal::Get(surface.get());
		activeModal->SetMessage("Game Paused");

		activeModal->SetCancelText("   Quit   ");
		activeModal->SetOnCancel([this]()
			{
				game->SwitchLevel<MainMenu>("");
			});

		activeModal->SetAcceptText(" Continue ");
		activeModal->SetOnAccept([this]() { activeModal = nullptr; });

		activeModal->SetOptionalText(" Restart ");
		activeModal->SetOnOptional([this]()
			{
				game->SwitchLevel<GameLevel>(name);
			});
		// Need to reference this level

		// find other keys here: http://sdl.beuc.net/sdl.wiki/SDLKey
		return;
	}
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

				//TODO some forloop math should allow us to not even try and waste on this corner check 
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
#undef GameStateWrapperInjection