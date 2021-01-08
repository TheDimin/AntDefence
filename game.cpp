#include "game.h"
#include <iostream>
#include <SDL_mouse.h>

#include "surface.h"
#include "Engine/LevelHelper.h"
#include "Game/GameLevel.h"

using namespace Tmpl8;


Game::~Game()
{
	delete LoadedLevel;
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	//Load default level
	LoadedLevel = LevelHelper::Load<GameLevel>("Test");
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

static Sprite oof(new Tmpl8::Surface("assets/Levels/Test/test.png"), 1);
static int frame = 0;

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

	for (IRenderable* IRender : Renderables)
	{
		IRender->Render(screen);
	}


}

void Game::MouseDown(int button)
{
	if (button != 1)
		return;
	int x, y = 0;
	SDL_GetMouseState(&x, &y);

	LoadedLevel->OnMouseDown(Tmpl8::vec2((float)x, (float)y));

	for (auto& element : LoadedLevel->uiContainer->Elements)
	{
		element->OnMouseDown();
	}
}

void Game::MouseMove(int x, int y, int Ax, int Ay)
{
	LoadedLevel->OnMouseMove(vec2((float)x, (float)y));

	for (auto& element : LoadedLevel->uiContainer->Elements)
	{
		element->OnMouseMove(x, y);
	}
}
