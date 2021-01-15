#include "MainMenu.h"
#include <string>
#include <iostream>
#include <filesystem>

#include "GameLevel.h"
#include "../game.h"
#include "../Engine/LevelHelper.h"
#include "../Engine/UI/UiButton.h"

namespace fs = std::filesystem;
std::string Trash = "asfsaf";

void MainMenu::CreateUI(UiContainer* UI)
{

	UI->Button(100, 100, 50, 50)->SetOnClick([this]()
		{
			if (SelectedLevelIndex == (int)AllLevelsInfo.size() - 1)
				SelectedLevelIndex = -1;

			SelectedLevel = AllLevelsInfo[++SelectedLevelIndex];
		})->SetText(&Trash);
		StyleInfo styleInfo = StyleInfo();
		UI->Button(230, 100, 50, 50)->SetOnClick([this]()
			{
				game->SwitchLevel<GameLevel>(SelectedLevel.name);
			})->SetText(&SelectedLevel.name);

}

void MainMenu::OnLoad()
{
	for (auto& file : fs::directory_iterator("assets/levels"))
	{
		if (fs::exists(file.path().string() + "/Level.json") && fs::exists(file.path().string() + "/Style.json"))
			AllLevelsInfo.insert(end(AllLevelsInfo), LevelInfo{ file.path().filename().string() });
	}
	SelectedLevel = AllLevelsInfo[0];

}

void from_json(const nlohmann::json& nlohmann_json_j, MainMenu& lvl)
{
}
