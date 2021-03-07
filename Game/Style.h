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
	std::unique_ptr<Tmpl8::Sprite> asset;
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
	std::unique_ptr<Tmpl8::Sprite> asset;
};

struct StatInfo
{
	ObjectStat* stat;
	float amount = 0;
};

struct MobData
{
private:
	friend void from_json(const nlohmann::json& json, MobData& mapSprite);
public:
	int id = -1;
	std::string displayName = "NONE";
	uint moneyOnKill = 0;
	float speed = 1;
	int damage = 1;
	std::unique_ptr<Tmpl8::Sprite> asset;
	std::vector<std::unique_ptr<StatInfo>> stats;

	StatInfo* FindStat(int id);
};

struct TowerUpgrade
{
	int id = -1;
	int price = 0;
	std::string displayName;
	std::vector<std::unique_ptr<StatInfo>> stats;
	std::vector<int> unLockedBy;
	std::vector<int> LockedBy;
};

struct TowerData
{
	int id = -1;
	std::string displayName = "Undefined";
	int price = 0;
	std::unique_ptr<Tmpl8::Sprite> asset;
	std::vector<std::unique_ptr<StatInfo>> stats;
	float range;
	StatInfo* FindStat(int id);
private:
	friend void from_json(const nlohmann::json& json, TowerData& towerData);
};

struct WaveSpawnInfo
{
	float delay = 0;
	float interval = 0;
	MobData* mob = nullptr;
	int amount = 0;
};

struct AttackWave
{
	int id;
	uint moneyOnComplete = 0;
	std::vector<WaveSpawnInfo> waves;
private:
	friend void from_json(const nlohmann::json& json, AttackWave& towerData);
};

class Style
{
public:
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

