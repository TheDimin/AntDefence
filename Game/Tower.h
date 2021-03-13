#pragma once

#include "Style.h"
#include "../Engine/GameObject.h"
#include "TowerStates/TowerFSM.h"

#define GameStateWrapperInjection(Function,ParamType,ParamName)	\
	void Function(ParamType ParamName) override {			\
		GameObject::Function(ParamName);							\
		towerFSM->Function(ParamName);}					\

class GameLevel;

class Tower :
	public GameObject
{
public:
	Tower(TowerData* towerData, Tmpl8::vec2 tile, Tmpl8::vec2 location, Tmpl8::vec2 size);

private:
	void SetLvl(Level* lvl) override;
public:
	//GameStateWrapperInjection(Tick, float, deltaTime);
	//GameStateWrapperInjection(Render, Tmpl8::Surface*, surface);

	void Tick(float deltaTime);
	void Render(Tmpl8::Surface* surface) override;


	friend class TowerAttackingState;
	Tmpl8::vec2 tile;
	GameLevel* gLVL = nullptr;
	TowerData* towerData = nullptr;
	float AttackTimer = 1;
	std::unique_ptr<TowerFSM> towerFSM;

	int rotation = 0;

	float ShotTimer = 0;
};

#undef GameStateWrapperInjection