#include "Level.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>


void Level::OnLevelLoaded()
{
	for (auto& obj : objects)
	{
		obj->OnLoad();
	}
}

std::string Level::GetLevelName()
{
	return name;
}

std::string lol = "SUB RETARD";
void Level::CreateUI(UiContainer* UI)
{
	UI->Button(90, 35, 80, 20, &lol);
	//UIHelpers::Button(10, 10, 5, 5, &lol);
}

Level* Level::Load(std::string LevelName)
{
	nlohmann::json j;
	std::ifstream file;
	Level* level = new Level();
	level->name = LevelName;
	level->surface = std::make_unique<Tmpl8::Surface>(EngineGlobal::GetWidth(), static_cast<int>(0.8f * EngineGlobal::GetHeight()));
	level->uiContainer = std::make_unique<UiContainer>(nullptr, EngineGlobal::GetWidth(), static_cast<int>(0.2f * EngineGlobal::GetHeight()));

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

	level->CreateUI(level->uiContainer.get());

	return level;
}

void from_json(const nlohmann::json& nlohmann_json_j, Level& lvl)
{
	std::vector<std::unique_ptr<MapSprite>>* mapSprites = &lvl.mapStyle->sprites;
	Tmpl8::Surface* surface = lvl.surface.get();

	size_t yAmount = nlohmann_json_j.at("map").size();
	size_t xAmount = nlohmann_json_j.at("map")[0].size();

	int w =static_cast<int>( 1.0f / static_cast<float>(xAmount) * static_cast<float>(surface->GetWidth())); //(xAmount / ((float)mapSprite->asset->GetWidth() * mapSprite->scale) * 0.8f);
	auto h = static_cast<int>(1.0f / static_cast<float>(yAmount) * static_cast<float>(surface->GetHeight()));

	int y = 0;
	for (auto& element : nlohmann_json_j.at("map").items()) {
		int x = 0;

		for (auto& id : element.value().get<std::vector<int>>()) {
			MapSprite* mapSprite = mapSprites->at(id).get();
			//mapSprite->asset->Draw(surface, mapSprite->asset->GetHeight() * y * mapSprite->scale, mapSprite->asset->GetWidth() * x * mapSprite->scale);
			 //(yAmount / ((float)mapSprite->asset->GetHeight() * mapSprite->scale) * 0.8f);

			mapSprite->asset->DrawScaled(w * x, h * y, w, h, surface);
			x++;
		}
		y++;
	}
}

