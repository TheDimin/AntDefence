#pragma once
#include "../Engine/Level.h"
#include "../Engine/GameObject.h"

struct LevelInfo
{
	std::string name;
};

class MainMenu :
	public Level
{
	friend class Game;

	friend void from_json(const nlohmann::json& nlohmann_json_j, MainMenu& lvl);
protected:
	void CreateUI(UiContainer* UI) override;
	void OnLoad() override;

	std::vector<LevelInfo> AllLevelsInfo;
	LevelInfo SelectedLevel;
	int SelectedLevelIndex = 0;

	Game* game;//Warning this is not available onload/creatUI , but will be in in lambda's 

};

