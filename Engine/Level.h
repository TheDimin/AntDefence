#pragma once
#include <vector>
#include "EngineGlobal.h"
#include "../surface.h"
#include "../Game/Style.h"
#include "UI/UIContainer.h"

class Level :ITickable, IRenderable
{
private:
	void OnLevelLoaded();

public:
	Level();
	virtual ~Level() = default;

	friend void from_json(const nlohmann::json& nlohmann_json_j, Level& lvl);
	std::string GetLevelName() const;

	int TileWidthCount, TileHeightCount = 0;
	std::unique_ptr<Style> mapStyle = std::make_unique<Style>();

	float CalculateTileWidth();
	float CalculateTileHeight();
	MapSprite* GetMapSprite(int width, int height);

	virtual void RegisterObject(class GameObject* obj);
	virtual void DeleteObject(class GameObject* obj);

public:
	virtual void Render(Tmpl8::Surface* surface) override;
	void Tick(float deltaTime) override;


	virtual void OnMouseMove(vec2 mousePos)
	{
		uiContainer->OnMouseMove(mousePos);
	}
	virtual void OnLeftClick(vec2 mousePos)
	{
		uiContainer->OnMouseDown();
	}
	virtual void OnRightMouseButtonDown() {}

protected:
	friend class LevelHelper; friend class Game;
	std::string name = "UNDEFINED";
	std::unique_ptr<Tmpl8::Surface> surface;
	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<std::vector<int>> mapTiles;
	std::vector<GameObject*> ToDeleteObjects = std::vector<GameObject*>();

protected:
	virtual void OnLoad() {};
	virtual void CreateUI(UiContainer* UI) = 0;
	std::unique_ptr<UiContainer> uiContainer;

};


