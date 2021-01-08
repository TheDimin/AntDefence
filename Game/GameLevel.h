#pragma once
#include "../Engine/Level.h"
#include "GameStates/GameFSM.h"

#define GameStateWrapperInjection(Function,ParamType,ParamName)	\
	void Function(ParamType ParamName) override {			\
		Level::Function(ParamName);							\
		gameState->Function(ParamName);}					\

class Mob;

class GameLevel :public Level
{
public:
	GameLevel();
	~GameLevel() = default;

public:
	friend void from_json(const nlohmann::json& nlohmann_json_j, GameLevel& lvl);
	void RegisterObject(GameObject* obj) override;
	bool CanPlaceTower(float x, float y, TowerData* tower);
public:
	std::unique_ptr<GameFSM> gameState;
	std::vector<std::pair<Tmpl8::vec2, GameObject*>>placedTowers;
	std::vector<Mob*> activeMobs = std::vector<Mob*>();
	int activeMobCount = 0;

public:
	int waveIndex = -1;
	AttackWave* waveInstance = nullptr;
	int waveStep = 0;
	int spawnedOfCurrentMobType = 0;
	float waveTimer = 0;
	bool completedSubWave = false;
	void StartNextWave();
	std::vector<vec2> route;

public:
	uint GetMoney() const;
	bool SpendMoney(uint amount);
	void AddMoney(uint amount);
	bool TakeDamage(int amount);

protected:
	uint Money = 100;
	int Health = 100;

protected://text ptr's 
	std::string MoneyText = "Money: 100";
	std::string HealthText = "Health: 100";
	std::string StartNextWaveText = "Start wave";

public:
	GameStateWrapperInjection(Render, Surface*, surface);
	GameStateWrapperInjection(OnMouseMove, vec2, pos);
	GameStateWrapperInjection(OnMouseDown, vec2, pos);
	void Tick(float deltaTime) override;

	void CreateUI(UiContainer* UI) override;
};
#undef GameStateWrapperInjection;