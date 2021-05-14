#include "MainMenu.h"
#include <string>
#include <iostream>
#include <filesystem>

#include "GameLevel.h"
#include "../game.h"
#include "../UICredits.h"
#include "../Engine/LevelHelper.h"
#include "../Engine/UI/UiButton.h"
#include "../Engine/UI/UIImage.h"
#include "../Engine/UI/UIModal.h"
#include "../Engine/UI/UIText.h"

namespace fs = std::filesystem;
std::string NextLvlText = "Next level";
std::string CreditsText = "Credits";
std::string CloseCreditsText = "Close";


void MainMenu::CreateUI(UiContainer* UI)
{

	UIButton* SelectedLevelButton = UI->Button(100, 720 - 180, 80, 25);
	UIButton* PageSelectButton = UI->Button(100, 720 - 90, 80, 25);

	UIButton* CreditsButton = UI->Button(100, 720, 80, 25);

	UIImage* Logo = UI->Image(10, 80, 180, 180, new Sprite(new Surface("assets/Logo.png"), 1));

	UIImage* image = UI->Image(200, 50, ScreenWidth - 250, ScreenHeight - 100, SelectedLevel.background);

	PageSelectButton->SetOnClick([this, image]()
		{
			if (SelectedLevelIndex == (int)AllLevelsInfo.size() - 1)
				SelectedLevelIndex = -1;

			SelectedLevel = AllLevelsInfo[++SelectedLevelIndex];

			image->SetSprite(SelectedLevel.background);
		});
	PageSelectButton->SetText(&NextLvlText);

	SelectedLevelButton->SetOnClick([this]()
		{
			game->SwitchLevel<GameLevel>(SelectedLevel.name);
		});
	SelectedLevelButton->SetText(&SelectedLevel.name);


	CreditsButton->SetText(&CreditsText);
	CreditsButton->SetOnClick([UI, this]()
		{
			UiContainer* CreditsPanel = UI->Container(0, 0, ScreenWidth, ScreenHeight, false);
			CreditsPanel->SetBackGroundColor(0x808080);

			int offset = 50;

			CreditsPanel->Text(static_cast<int>((float)ScreenWidth * 0.5f), offset, 10, "Ant Defence")->SetTextCentert(true);
			CreditsPanel->Text(static_cast<int>((float)ScreenWidth * 0.5f), offset += 120, 5, "Intake assignment project for BUAS")->SetTextCentert(true);
			CreditsPanel->Text(static_cast<int>((float)ScreenWidth * 0.5f), offset += 80, 5, "Made by Damian van Hoorn")->SetTextCentert(true);
			CreditsPanel->Text(static_cast<int>((float)ScreenWidth * 0.5f), offset += 100, 8, "Special thanks to:")->SetTextCentert(true);
			CreditsPanel->Text(static_cast<int>((float)ScreenWidth * 0.5f), offset += 80, 4, "https://www.kenney.nl/ (Background sprites)")->SetTextCentert(true);
			CreditsPanel->Text(static_cast<int>((float)ScreenWidth * 0.5f), offset += 80, 4, "Github.com/nlohmann/json (Json implementation)")->SetTextCentert(true);


			UIButton* CloseButton = CreditsPanel->Button((int)((float)ScreenWidth * 0.5f), (int)((float)ScreenHeight * 0.9f), 100, 30);
			CloseButton->SetOnClick([this]()
				{
					game->SwitchLevel<MainMenu>("MainMenu");
				});
			CloseButton->SetText(&CloseCreditsText);
		});
}

void MainMenu::OnLoad()
{
	Level::OnLoad();
	for (auto& file : fs::directory_iterator("assets/levels"))
	{
		if (fs::exists(file.path().string() + "/Level.json") && fs::exists(file.path().string() + "/Style.json"))
		{
			nlohmann::json j;
			std::ifstream(file.path().string() + "/Level.json") >> j;
			std::string spritePath;
			j.at("PreviewImage").get_to(spritePath);
			AllLevelsInfo.insert(end(AllLevelsInfo), LevelInfo{ file.path().filename().string(),new  Sprite(new Surface(const_cast<char*>((file.path().string() + "/" + spritePath).c_str())),1) });
		}

	}
	SelectedLevel = AllLevelsInfo[0];

}

void from_json(const nlohmann::json& nlohmann_json_j, MainMenu& lvl)
{
}
