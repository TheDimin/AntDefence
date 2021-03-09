#pragma once
#include <string>
#include <fstream>
#include <utility>


#include "../Game/MainMenu.h"
#include "UI/UIContainer.h"

class LevelHelper
{
public:

	template<class LevelType>
	static LevelType* Load(std::string LevelName);
};



template <class LevelType>
LevelType* LevelHelper::Load(std::string LevelName)
{
	static_assert(std::is_base_of<Level, LevelType>::value, "Load level template param should be of type Level");

	nlohmann::json j;
	std::ifstream file;
	LevelType* level = new LevelType();
	level->name = LevelName;
	level->surface = std::make_unique<Tmpl8::Surface>(EngineGlobal::GetWidth(), static_cast<int>(0.8f * EngineGlobal::GetHeight()));
	level->uiContainer = std::make_unique<UiContainer>(vec2(0, (int)ceil(EngineGlobal::GetHeight() * 0.8f)), EngineGlobal::GetWidth(), static_cast<int>(0.2f * EngineGlobal::GetHeight()));

	file.close(); j.clear();

	file = std::ifstream("assets/Levels/" + LevelName + "/Style.json");
	file >> j;
	level->mapStyle = std::make_unique<Style>();
	level->mapStyle->level = level;
	j.get_to(level->mapStyle);

	file = std::ifstream("assets/Levels/" + LevelName + "/Level.json");

	if (!file.is_open())
	{
		std::cout << "Failed to load level : '" << LevelName << "'" << std::endl;
		return level;
	}

	file >> j;

	j.get_to(*level);

	level->OnLevelLoaded();

	return level;
}

template <>
inline MainMenu* LevelHelper::Load<MainMenu>(std::string _)
{
	nlohmann::json j;
	std::ifstream file;
	MainMenu* level = new MainMenu();
	level->name = "MainMenu";
	level->surface = std::make_unique<Tmpl8::Surface>(EngineGlobal::GetWidth(), EngineGlobal::GetHeight());
	level->uiContainer = std::make_unique<UiContainer>(vec2(0, 0), EngineGlobal::GetWidth(), EngineGlobal::GetHeight());

	/*file.close(); j.clear();

	file = std::ifstream("assets/Levels/" + LevelName + "/Style.json");
	file >> j;
	level->mapStyle = std::make_unique<Style>();
	level->mapStyle->level = level;
	j.get_to(level->mapStyle);

	file = std::ifstream("assets/Levels/" + LevelName + "/Level.json");

	if (!file.is_open())
	{
		std::cout << "Failed to load level : '" << LevelName << "'" << std::endl;
		return level;
	}

	file >> j;

	j.get_to(*level);
*/
	level->OnLevelLoaded();

	return level;
}