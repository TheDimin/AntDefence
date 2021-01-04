#include "Style.h"
#include <iostream>
#include <string>

#include "json.hpp"
#include "json_fwd.hpp"
#include "../Engine/Level.h"

Style* styleInstance;
std::string filePath = "NULL";

#define MapJsonData(valueName,source) json.at(#valueName).get_to(source.valueName);

void from_json(const nlohmann::json& json, MapSprite& mapSprite)
{
	MapJsonData(scale, mapSprite);

	const std::string filepath = filePath + json.at("asset").get<std::string>();
	mapSprite.asset = new Tmpl8::Sprite(new Tmpl8::Surface(const_cast<char*>(filepath.c_str())), 1);


	if (json.contains("canBuild"))
		json.at("canBuild").get_to(mapSprite.canBuild);
	else if (json.contains("canWalk"))
		json.at("canWalk").get_to(mapSprite.canWalk);
}

void from_json(const nlohmann::json& json, ObjectStat& objectStat)
{
	MapJsonData(displayName, objectStat);
	MapJsonData(id, objectStat);

	const std::string filepath = filePath + json.at("asset").get<std::string>();
	objectStat.asset = new Tmpl8::Sprite(new Tmpl8::Surface(const_cast<char*>(filepath.c_str())), 1);
}

void from_json(const nlohmann::json& json, StatInfo& mapSprite)
{

}

void from_json(const nlohmann::json& json, MobData& mapSprite)
{
	MapJsonData(id, mapSprite);
	MapJsonData(displayName, mapSprite);
	MapJsonData(speed, mapSprite);
	MapJsonData(moneyOnKill, mapSprite);

	const std::string filepath = filePath + json.at("asset").get<std::string>();
	mapSprite.asset = new Tmpl8::Sprite(new Tmpl8::Surface(const_cast<char*>(filepath.c_str())), 1);

	for (auto& elem : json["stats"].items())
	{
		mapSprite.stats.insert(end(mapSprite.stats), StatInfo{ styleInstance->FindStat(elem.value()["id"]), elem.value()["amount"] });
	}
}


void from_json(const nlohmann::json& json, TowerData& towerData)
{
	MapJsonData(id, towerData);
	MapJsonData(displayName, towerData);
	MapJsonData(price, towerData);

	const std::string filepath = filePath + json.at("asset").get<std::string>();
	towerData.asset = new Tmpl8::Sprite(new Tmpl8::Surface(const_cast<char*>(filepath.c_str())), 1);

	for (auto& elem : json["stats"].items())
	{
		towerData.stats.insert(end(towerData.stats), StatInfo{ styleInstance->FindStat(elem.value()["id"]), elem.value()["amount"] });
	}
	//TODO UPGRADES
}


void from_json(const nlohmann::json& json, AttackWave& attackWave)
{
	MapJsonData(delay, attackWave);
	MapJsonData(moneyOnComplete, attackWave);

	for (auto& elem : json["mobs"].items())
	{
		attackWave.waves.insert(end(attackWave.waves), WaveSpawnInfo{ styleInstance->FindMob(elem.value()["id"]), elem.value()["amount"] });
	}
}

void from_json(const nlohmann::json& cjson, Style& style)
{
	styleInstance = &style;
	nlohmann::json json = (nlohmann::json)cjson;

	filePath = "assets/Levels/" + style.level->GetLevelName() + "/";

	MapJsonData(map, style);
	MapJsonData(stats, style);

	MapJsonData(towers, style);
	MapJsonData(mobs, style);

	MapJsonData(waves, style);

	printf("Mob TEST: %u", style.mobs[0].get()->stats[0].amount);
}

ObjectStat* Style::FindStat(int id)
{
	return std::find_if(begin(stats), end(stats), [id](std::unique_ptr<ObjectStat>& stat) {return stat->id == id; })->get();
}

MobData* Style::FindMob(int id)
{
	auto it = std::find_if(begin(mobs), end(mobs), [id](std::unique_ptr<MobData>& stat) {return stat->id == id; });
	if (it == end(mobs))
	{
		throw std::logic_error("Failed to find mobID: " + std::to_string(id));
	}


	return it->get();
}

AttackWave* Style::GetWave(int id)
{
	return waves[id].get();
}