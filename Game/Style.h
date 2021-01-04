#pragma once
#include "json_fwd.hpp"
#include "../surface.h"
#include "../template.h"

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

struct ObjectStat
{
public:
	ObjectStat() = default;

private:
	friend void from_json(const nlohmann::json& json, ObjectStat& mapSprite);
public:
	int id = -1;
	std::string displayName = "NONE";
	Tmpl8::Sprite* asset;
};

struct StatInfo
{
	ObjectStat* stat;
	int amount = 0;
};

struct MobData
{
private:
	friend void from_json(const nlohmann::json& json, MobData& mapSprite);
public:
	int id = -1;
	std::string displayName = "NONE";
	float moneyOnKill = 0;
	float speed = 1;
	Tmpl8::Sprite* asset;
	std::vector<StatInfo> stats;
};

struct TowerUpgrade
{
	int id = -1;
	int price = 0;
	std::string displayName;
	std::vector<StatInfo> stats;
	std::vector<int> unLockedBy;
	std::vector<int> LockedBy;
};

struct TowerData
{
	int id = -1;
	std::string displayName = "Undefined";
	int price = 0;
	Tmpl8::Sprite* asset;
	std::vector<StatInfo> stats;
private:
	friend void from_json(const nlohmann::json& json, TowerData& towerData);
};

struct WaveSpawnInfo
{
	MobData* mob;
	int amount = 0;
};

struct AttackWave
{
	float delay = 0;
	uint moneyOnComplete = 0;
	std::vector<WaveSpawnInfo> waves;
private:
	friend void from_json(const nlohmann::json& json, AttackWave& towerData);
};

class Style
{
public:
	Style() = default;
	class Level* level;
public:
	std::vector<std::unique_ptr<MapSprite>> map = std::vector<std::unique_ptr<MapSprite>>();
	std::vector<std::unique_ptr<TowerData>> towers = std::vector<std::unique_ptr<TowerData>>();
	std::vector<std::unique_ptr<ObjectStat>> stats = std::vector<std::unique_ptr<ObjectStat>>();
	std::vector<std::unique_ptr<MobData>> mobs = std::vector<std::unique_ptr<MobData>>();
	std::vector<std::unique_ptr<AttackWave>> waves = std::vector<std::unique_ptr<AttackWave>>();
public:
	ObjectStat* FindStat(int id);
	MobData* FindMob(int id);
	AttackWave* GetWave(int id);

public:
	friend void from_json(const nlohmann::json& json, Style& style);
};

