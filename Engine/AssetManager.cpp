#include "AssetManager.h"

#include <fstream>
#include <iostream>

#include "json.hpp"

void AssetManager::Load(std::string LevelName)
{
	std::ifstream file = std::ifstream("assets/Levels/" + LevelName + "/Style.json");

	if (!file.is_open())
	{
		std::cout << "Failed to load level : '" << LevelName << "'" << std::endl;
	}

	nlohmann::json j;
	file >> j;
}
