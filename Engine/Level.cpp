#include "Level.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>

#include "UI/UIButton.h"


void Level::OnLevelLoaded()
{
	//uiContainer->Init(uiContainer->Pos, uiContainer->Scale, uiContainer->Offset);
	OnLoad();
	CreateUI(uiContainer.get());

	for (auto& obj : objects)
	{
		obj->OnLoad();
	}
}

Level::Level()
{
	uiContainer = std::make_unique<UiContainer>(vec2(0, 0), 0, (int)ceil(EngineGlobal::GetHeight() * 0.8f));
}

std::string Level::GetLevelName() const
{
	return name;
}

float Level::CalculateTileWidth()
{
	return ceil(1.0f / static_cast<float>(TileWidthCount) * static_cast<float>(surface->GetWidth()));
}

float Level::CalculateTileHeight()
{
	return  ceil(1.0f / static_cast<float>(TileHeightCount) * static_cast<float>(surface->GetHeight()));
}

MapSprite* Level::GetMapSprite(int width, int height)
{
	if (maptiles.size() <= height) { assert("Level::GetMapSprites Height out of range"); return nullptr; }
	if (maptiles[height].size() <= width) { assert("Level::GetMapSprites Width out of range"); return nullptr; }

	int tileStyle = maptiles[height][width];

	return mapStyle->map[tileStyle].get();
}

void Level::RegisterObject(GameObject* obj)
{
	objects.insert(begin(objects), std::unique_ptr<GameObject>(obj));
	obj->SetLvl(this);
}

void Level::DeleteObject(GameObject* obj)
{
	//https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object

	if (std::find(begin(ToDeleteObjects), end(ToDeleteObjects), obj) == end(ToDeleteObjects))
		ToDeleteObjects.insert(end(ToDeleteObjects), obj);
}

void Level::Render(Surface* surface)
{
	for (auto& element : objects)
	{
		if (element != nullptr)
			element->Render(surface);
	}
}

void Level::Tick(float deltaTime)
{
	for (auto& obj : objects)
	{
		obj->Tick(deltaTime);
	}

	for (auto& obj : ToDeleteObjects)
	{
		auto toErase = std::remove_if(begin(objects), end(objects),
			[&obj](std::unique_ptr<GameObject>& sObj)
			{
				return sObj.get() == obj;
			});

		if (toErase != end(objects))
		{
			delete toErase->get();
			objects.erase(toErase);
		}
		else
			printf("HEY FAILED TO DESTROY OBJECT REF \n");
	}
	ToDeleteObjects.resize(0);
}

void from_json(const nlohmann::json& nlohmann_json_j, Level& lvl)
{
	std::vector<std::unique_ptr<MapSprite>>* mapSprites = &lvl.mapStyle->map;
	Tmpl8::Surface* surface = lvl.surface.get();

	//	TileWidthCount, TileHeightCount
	lvl.TileHeightCount = (int)nlohmann_json_j.at("map").size();
	lvl.TileWidthCount = (int)nlohmann_json_j.at("map")[0].size();

	lvl.maptiles = std::vector<std::vector<int>>();

	float width = lvl.CalculateTileWidth();
	float height = lvl.CalculateTileHeight();
	int y = 0;
	for (auto& element : nlohmann_json_j.at("map").items()) {
		int x = 0;
		auto row = std::vector<int>();
		for (auto& id : element.value().get<std::vector<int>>()) {
			MapSprite* mapSprite = mapSprites->at(id).get();
			row.insert(end(row), id);
			//mapSprite->asset->Draw(surface, mapSprite->asset->GetHeight() * y * mapSprite->scale, mapSprite->asset->GetWidth() * x * mapSprite->scale);
			 //(yAmount / ((float)mapSprite->asset->GetHeight() * mapSprite->scale) * 0.8f);

			mapSprite->asset->DrawScaled((int)width * x, (int)height * y, (int)width, (int)height, surface);
			x++;
		}
		lvl.maptiles.insert(end(lvl.maptiles), row);
		y++;
	}
}

