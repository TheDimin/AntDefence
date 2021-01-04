#pragma once
#include "../../template.h"
#include "../../Engine/FSM/Event.h"

struct TowerData;

class PlaceBuildingEvent :
	public Event
{
public:
	PlaceBuildingEvent(const Tmpl8::vec2& tile, const Tmpl8::vec2& location,const Tmpl8::vec2& size, TowerData* tower)
		: tile(tile),
		towerData(tower), location(location),size(size)
	{
	}

	Tmpl8::vec2 tile;
	Tmpl8::vec2 location;
	Tmpl8::vec2 size;
	TowerData* towerData;
};

