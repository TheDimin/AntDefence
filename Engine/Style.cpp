#include "Game/Style.h"
#include <iostream>
#include <string>
#include "Engine/Level.h"

void from_json(const nlohmann::json& json, MapSprite& mapSprite)
{
	json.at("scale").get_to(mapSprite.scale);

	const std::string filepath = json.at("path").get<std::string>() + json.at("asset").get<std::string>();
	mapSprite.asset = new Tmpl8::Sprite(new Tmpl8::Surface(const_cast<char*>(filepath.c_str())), 1);


	if (json.contains("canBuild"))
		json.at("canBuild").get_to(mapSprite.canBuild);
	else if (json.contains("canWalk"))
		json.at("canWalk").get_to(mapSprite.canWalk);
}

void from_json(const nlohmann::json& cjson, Style& style)
{
	nlohmann::json json = (nlohmann::json)cjson;

	for (auto& elem : json["map"].items())
	{
		elem.value()["path"] = "assets/Levels/" + style.level->GetLevelName() + "/";
	}

	json.at("map").get_to(style.sprites);
}