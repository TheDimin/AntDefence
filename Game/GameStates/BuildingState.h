#pragma once
#include "GameState.h"

namespace Tmpl8 {
	class Sprite;
}

struct TowerData;

class BuildingState : public GameState
{
public:
	BuildingState();
	~BuildingState();
public:
	void OnStateEnter(Event* e) override;
	void OnStateExit(Event* newEvent) override;
	void Tick(float deltaTime) override;
	void OnLeftClick(Tmpl8::vec2& mousePos) override;
	void Render(Tmpl8::Surface* surface) override;
	void OnMouseMove(Tmpl8::vec2& mousePos) override;

	TowerData* SelectedBuildTower = nullptr;
	Tmpl8::vec2 mousePos;
	Tmpl8::Sprite* circleSprite;
};


