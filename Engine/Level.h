#pragma once
#include <vector>
#include "EngineGlobal.h"
#include "GameObject.h"
#include "../surface.h"
#include "../Game/Style.h"
#include "UI/UIContainer.h"

class Level
{
public:
	void OnLevelLoaded();

public:
	Level() = default;
	virtual ~Level() = default;

	friend void from_json(const nlohmann::json& nlohmann_json_j, Level& lvl);
	std::string GetLevelName() const;

	int TileWidthCount, TileHeightCount = -1;
	std::unique_ptr<Style> mapStyle = std::make_unique<Style>();

	float CalculateTileWidth();
	float CalculateTileHeight();
	MapSprite* GetMapSprite(int width, int height);

	virtual void RegisterObject(GameObject* obj);

protected:
	virtual void Draw(Surface* surface)
	{
		for (auto& element : objects)
		{
			element->Render(surface);
		}
	};

	virtual void Update(float deltaTime) {};
	virtual void OnMouseMove(vec2 pos) {};
	virtual void OnMouseDown(vec2 pos) {};

protected:
	friend class LevelHelper; friend class Game;
	std::string name = "UNDEFINED";
	std::unique_ptr<Tmpl8::Surface> surface;
	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<std::vector<int>> maptiles;
protected:
	virtual void CreateUI(UiContainer* UI) = 0;
	std::unique_ptr<UiContainer> uiContainer;
};


