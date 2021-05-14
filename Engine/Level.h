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
	int TileWidthCount, TileHeightCount = 0;
	std::unique_ptr<Style> mapStyle = std::make_unique<Style>();

	float CalculateTileWidth();
	float CalculateTileHeight();

	MapSprite* GetMapSprite(int width, int height);

	virtual void RegisterObject(class GameObject* obj);
	virtual void DeleteObject(class GameObject* obj);
	virtual bool IsPaused() const;

	bool IsValid(GameObject* object);

	std::string GetLevelName() const;
protected:
	friend class LevelHelper; friend class Game;
	/// <summary>
	/// Name of the currently loaded level
	/// </summary>
	std::string name = "UNDEFINED";
	/// <summary>
	/// screen space the level can draw on
	/// </summary>
	std::unique_ptr<Tmpl8::Surface> surface;
	/// <summary>
	/// Objects that are spawned in the level
	/// </summary>
	std::vector<std::unique_ptr<GameObject>> objects;
	/// <summary>
	/// Tiles making up the level
	/// </summary>
	std::vector<std::vector<int>> mapTiles;
	/// <summary>
	/// Objects that are pending destroy at the end of the frame
	/// </summary>
	std::vector<GameObject*> ToDeleteObjects = std::vector<GameObject*>();
	bool Paused = false;
	/// <summary>
	/// Reference to the game instance
	/// </summary>
	Game* game;
	/// <summary>
	/// UiContainer we own
	/// </summary>
	std::unique_ptr<UiContainer> uiContainer;

public:
	/// <summary>
	/// Tick event for drawing objects to UI
	/// </summary>
	/// <param name="surface">Surface you should draw to</param>
	virtual void Render(Tmpl8::Surface* surface) override;

	/// <summary>
	/// GameTick used for all game play logic
	/// </summary>
	/// <param name="deltaTime">The time that has passed since the last tick</param>
	void Tick(float deltaTime) override;


	/// <summary>
	/// Event called when user moves his mouse
	/// </summary>
	/// <param name="mousePos"> The posistion of the mouse on screen</param>
	virtual void OnMouseMove(vec2 mousePos)
	{
		uiContainer->OnMouseMove(mousePos);
	}

	/// <summary>
	/// Event called when the user left clicks 
	/// </summary>
	/// <param name="mousePos">Position of the mouse when user left clicked</param>
	virtual void OnLeftClick(vec2 mousePos)
	{
		uiContainer->OnLeftClick();
	}

	/// <summary>
	/// Event called when user presses a key down
	/// </summary>
	/// <param name="key">Keycode of the pressed key</param>
	virtual void OnKeyDown(int key) {}


	/// <summary>
	/// Convert Json data to a instance of Level
	/// </summary>
	/// <param name="nlohmann_json_j">Json object</param>
	/// <param name="lvl">Level instance</param>
	friend void from_json(const nlohmann::json& nlohmann_json_j, Level& lvl);

protected:
	/// <summary>
	/// Level has loaded, good place to do level setup
	/// </summary>
	virtual void OnLoad()
	{
		//We need to get a global reference to the viewport
		EngineGlobal::SetDebugScreen(surface.get());
	}

	/// <summary>
	/// Ui has be initalized, Draw ui containers
	/// </summary>
	/// <param name="UI"></param>
	virtual void CreateUI(UiContainer* UI) = 0;
};


