#pragma once
#include <vector>
#include "EngineGlobal.h"
#include "GameObject.h"
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
	virtual bool IsPaused() const;

	bool IsValid(GameObject* object);


public:
	virtual void Render(Tmpl8::Surface* surface) override;
	void Tick(float deltaTime) override;


	virtual void OnMouseMove(vec2 mousePos)
	{
		uiContainer->OnMouseMove(mousePos);
	}
	virtual void OnLeftClick(vec2 mousePos)
	{
		uiContainer->OnLeftClick();
	}
	virtual void OnRightMouseButtonDown() {}
	virtual void OnKeyDown(int key) {}

protected:
	friend class LevelHelper; friend class Game;
	std::string name = "UNDEFINED";
	std::unique_ptr<Tmpl8::Surface> surface;
	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<std::vector<int>> mapTiles;
	std::vector<GameObject*> ToDeleteObjects = std::vector<GameObject*>();
	bool Paused = false;
	Game* game;
protected:
	virtual void OnLoad()
	{
		EngineGlobal::SetDebugScreen(surface.get());
	};
	virtual void CreateUI(UiContainer* UI) = 0;
	std::unique_ptr<UiContainer> uiContainer;

};


