#pragma once
#include <vector>
#include "EngineGlobal.h"
#include "GameObject.h"
#include "surface.h"
#include "UIContainer.h"
#include "Game/Style.h"

class Level
{
public:
	static Level* Load(std::string LevelName);
	void OnLevelLoaded();

public:
	Level() = default;

	friend void from_json(const nlohmann::json& nlohmann_json_j, Level& lvl);
	std::string GetLevelName();
private:
	friend class Game;
	std::unique_ptr<Style> mapStyle = std::make_unique<Style>();
	std::string name = "UNDEFINED";
	std::unique_ptr<Tmpl8::Surface> surface;
	std::vector<std::unique_ptr<GameObject>> objects;

protected:
	friend class Level;
	void CreateUI(UiContainer* UI);
	std::unique_ptr<UiContainer> uiContainer;
};

