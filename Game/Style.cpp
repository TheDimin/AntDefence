#include "Style.h"
#include <iostream>
#include <string>

#include "json.hpp"
#include "json_fwd.hpp"
#include "../Engine/Level.h"

Style* styleInstance;
std::string filePath = "NULL";

#define MapJsonData(valueName,source) json.at(#valueName).get_to(source.valueName);

Sprite* LoadSprite(const nlohmann::json& json,int frames)
{
	const std::string filepath = json.at("asset").get<std::string>();
	if (filepath.rfind("GLOBAL:") == 0)
	{
		return new Sprite(new Tmpl8::Surface(const_cast<char*>(("assets/Global/" + filepath.substr(7)).c_str())), frames);
	}

	return  new Sprite(new Tmpl8::Surface(const_cast<char*>((filePath + filepath).c_str())), frames);
}

void from_json(const nlohmann::json& json, MapSprite& mapSprite)
{
	MapJsonData(scale, mapSprite);


	mapSprite.asset = std::unique_ptr<Sprite>(LoadSprite(json,1));

	if (json.contains("canBuild"))
		json.at("canBuild").get_to(mapSprite.canBuild);
	else if (json.contains("canWalk"))
		json.at("canWalk").get_to(mapSprite.canWalk);
}

void from_json(const nlohmann::json& json, ObjectStat& objectStat)
{
	MapJsonData(id, objectStat);

	//const std::string filepath = filePath + json.at("asset").get<std::string>();
	//objectStat.asset = std::make_unique<Tmpl8::Sprite>(new Tmpl8::Surface(const_cast<char*>(filepath.c_str())), 1);
}

void from_json(const nlohmann::json& json, MobData& mopData)
{
	MapJsonData(id, mopData);
	MapJsonData(speed, mopData);
	MapJsonData(moneyOnKill, mopData);
	MapJsonData(damage, mopData);

	mopData.asset = std::unique_ptr<Sprite>(LoadSprite(json,12));

	for (auto& elem : json["stats"].items())
		mopData.stats.insert(end(mopData.stats), std::unique_ptr<StatInfo>(new StatInfo{ styleInstance->FindStat(elem.value()["id"]), elem.value()["amount"] }));

}


void from_json(const nlohmann::json& json, TowerData& towerData)
{
	MapJsonData(id, towerData);
	MapJsonData(price, towerData);
	MapJsonData(range, towerData);

	towerData.asset = std::unique_ptr<Sprite>(LoadSprite(json,5));

	for (auto& elem : json["stats"].items())
		towerData.stats.insert(end(towerData.stats), std::unique_ptr<StatInfo>(new StatInfo{ styleInstance->FindStat(elem.value()["id"]), elem.value()["amount"] }));

	//TODO UPGRADES
	/*
	 * "upgrades": [
				{
					"ID": -1,
					"Price" : 10,
					"DisplayName" : "Undefined",
					"Stats":[
						{
							"id":-1,
							"amount": 10
						}
					],

					"unLockedBy" :[],
					"LockedBy" : []
				}
			]
	 */
}


void from_json(const nlohmann::json& json, AttackWave& attackWave)
{

	for (auto& elem : json["mobs"].items())
	{
		float delay = (elem.value().contains("delay") ? elem.value()["delay"] : 0);
		float interval = elem.value().contains("interval") ? elem.value()["interval"] : -1;
		attackWave.waves.insert(end(attackWave.waves), WaveSpawnInfo{ delay, interval,styleInstance->FindMob(elem.value()["id"]), elem.value()["amount"] });
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
}

StatInfo* MobData::FindStat(int statID)
{
	return std::find_if(begin(stats), end(stats), [statID](std::unique_ptr<StatInfo>& stat) {return stat->stat->id == statID; })->get();
}

StatInfo* TowerData::FindStat(int statID)
{
	return std::find_if(begin(stats), end(stats), [statID](std::unique_ptr<StatInfo>& stat) {return stat->stat->id == statID; })->get();
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
