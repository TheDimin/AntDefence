#pragma once
#include "../../GameState.h"
#include "../../template.h"

struct TowerData;

class BuildingState : public GameState
{
public:
	void OnStateEnter(Event* e) override;
	void OnStateExit(Event* newEvent) override;
	void Update(float deltaTime) override;
	void OnMouseDown(Tmpl8::vec2& mousePos) override;
	void Draw(Tmpl8::Surface* surface) override;
	void OnMouseMove(Tmpl8::vec2& mousePos) override;
	
	TowerData* SelectedBuildTower;
	Tmpl8::vec2 mousePos;
};


