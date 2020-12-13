#pragma once
#include "EngineGlobal.h"
#include "surface.h"

struct  MapSprite
{
public:
	MapSprite() = default;

private:
	friend void from_json(const nlohmann::json& json, MapSprite& mapSprite);
public:
	Tmpl8::Sprite* asset;
	bool canBuild = false;
	bool canWalk = false;
	float scale = 1;
};

struct Stat
{
	int id = -1;
	std::string displayName;
	Tmpl8::Sprite Image;
};

struct StatInfo
{
	int id = -1;
	int amount = 0;
};

struct TowerUpgrade
{
	int id = -1;
	int price = 0;
	std::string DisplayName;
	std::vector<StatInfo> stats;
	std::vector<int> unLockedBy;
	std::vector<int> LockedBy;
};

struct Tower
{
	int id = -1;
	std::string DisplayName = "Undefined";
	int price = 0;
	Tmpl8::Sprite sprites;
	std::vector<StatInfo> stats;

};

class Style
{
public:
	Style() = default;
	class Level* level;
public:
	std::vector<std::unique_ptr<MapSprite>> sprites = std::vector<std::unique_ptr<MapSprite>>();

public:
	friend void from_json(const nlohmann::json& json, Style& style);
};

