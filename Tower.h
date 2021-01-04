#pragma once
#include "Engine/GameObject.h"
#include "Game/Style.h"

class Tower :
	public GameObject
{
public:
	Tower(TowerData* towerData, Tmpl8::vec2 tile, Tmpl8::vec2 location, Tmpl8::vec2 size) : GameObject(towerData->asset, location, size), tile(tile)
	{
		//MapSpriteData->PlacedTowerAtLocation = true;
	};

	~Tower()
	{
		//mapSprite->PlacedTowerAtLocation = false;
	}
	Tmpl8::vec2 tile;
};

