#include "game.h"
#include <iostream>
#include <SDL_mouse.h>

#include "surface.h"
#include "Engine/LevelHelper.h"
#include "Game/GameLevel.h"
#include "Game/MainMenu.h"

using namespace Tmpl8;


Game::~Game()
{
	delete NewLevel;
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	//Load default level
	MainMenu* mmLvl = LevelHelper::Load<MainMenu>("MainMenu");
	mmLvl->game = this;
	Game::LoadedLevel = std::unique_ptr<Level>(mmLvl);

	//
	//LoadedLevel->objects.insert(LoadedLevel->objects.begin(), std::make_unique<GameObject>());
	//std::cout << LoadedLevel->mapStyle->sprites[0]->asset << std::endl;
	//LoadedLevel->CreateUI(LoadedLevel->uiContainer.get());
	//std::cout << "FoundType: " << Reflect::Reflections::Get()->FindType("GameObject")->GetName() << std::endl;
}

// -----------------------------------------------------------
// Close down application
// -----------------------------------------------------------
void Game::Shutdown()
{
}

// -----------------------------------------------------------
// Main application tick function
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
	// clear the graphics window
	screen->Clear(0);
	LoadedLevel->Tick(deltaTime);

	LoadedLevel->surface->CopyTo(screen, 0, 0);
	LoadedLevel->Render(screen);
	LoadedLevel->uiContainer->Render(screen); // we could do some tricks to only update ui x times a second

//	for (IRenderable* IRender : Renderables)
	//{
	//	IRender->Render(screen);
	//}


	//Can only save switch lvl at end of the frame
	if (NewLevel != nullptr) {
		LoadedLevel = std::unique_ptr<Level>(NewLevel);
		NewLevel = nullptr;
	}

}

void Game::MouseDown(int button)
{
	int x, y = 0;
	SDL_GetMouseState(&x, &y);
	if (button == 1)
		LoadedLevel->OnLeftClick(Tmpl8::vec2((float)x, (float)y));
	else if (button == 3)
		std::cout << "button: " << button << std::endl;
}

void Game::MouseMove(int x, int y, int Ax, int Ay)
{
	LoadedLevel->OnMouseMove(vec2((float)x, (float)y));
}
