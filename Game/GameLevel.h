#pragma once
#include "../Engine/Level.h"
#include "GameStates/GameFSM.h"

#define GameStateWrapperInjection(Function,ParamType,ParamName)	\
	void Function(ParamType ParamName) override {			\
		Level::Function(ParamName);							\
		gameState->Function(ParamName);}					\

class GameLevel :public Level
{
public:
	GameLevel();
	~GameLevel() = default;

public:
	void RegisterObject(GameObject* obj) override;
	uint GetMoney() const;
	bool SpendMoney(uint amount);
	bool CanPlaceTower(float x, float y, TowerData* tower);
	std::unique_ptr<GameFSM> gameState;

	std::vector<std::pair<Tmpl8::vec2, GameObject*>>PlacedTowers;
protected:
	uint Money = 100;
	std::string MoneyText = "Money: 100";
protected:
	GameStateWrapperInjection(Draw, Surface*, surface);
	GameStateWrapperInjection(Update, float, deltaTime);
	GameStateWrapperInjection(OnMouseMove, vec2, pos);
	GameStateWrapperInjection(OnMouseDown, vec2, pos);

	void CreateUI(UiContainer* UI) override;
};
