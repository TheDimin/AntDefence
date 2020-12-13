#include "game.h"
#include <iostream>
#include <SDL_mouse.h>

#include "surface.h"

using namespace Tmpl8;


// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	//Load default level
	LoadedLevel = std::unique_ptr<Level>(Level::Load("Test"));
	//
	LoadedLevel->objects.insert(LoadedLevel->objects.begin(), std::make_unique<GameObject>());
	std::cout << LoadedLevel->mapStyle->sprites[0]->asset << std::endl;
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
	//LoadedLevel->mapStyle.sprites[0].asset->
	//	oof.Draw(screen, 10, 10);
	LoadedLevel->surface->CopyTo(screen, 0, 0);
	std::string l = "";

	LoadedLevel->uiContainer->Tick(); // we can do some tricks to only update ui x times a second

	LoadedLevel->uiContainer->surface->CopyTo(screen, 0, EngineGlobal::GetHeight() * 0.8f);

	for (IRenderable* IRender : Renderables)
	{
		IRender->Render(screen);
	}

	// print something in the graphics window
	//screen->Print("hello world", 2, 2, 0xffffff);
	// print something to the text window
//	printf("this goes to the console window.\n");
	// draw a sprite
	//std::cout << "FoundType" << Reflect::Reflections::Get()->FindType("GameObject") << std::endl;


	/*GameObject* tobj = new GameObject();
	tobj->lol = 420;
	PropInfo* propInfo = GameObject::GetType()->FindProp("lol");
	printf("current value:: %d \n", propInfo->TryGetValue<int>(tobj));

	int oooof = 10;

	propInfo->TrySetValue<int>(tobj, oooof);
	printf("Updated Value:: %d \n", propInfo->TryGetValue<int>(tobj));
	delete tobj;
	*/
	//screen->Print(, 2, 2, 0xffffff);


	//GameObject::GetType()->FindProp("lol")->TrySetValue(&tobj, &oooof);

	//screen->Print(const_cast<char*>(GameObject::GetType()->GetName().c_str()), 2, 2, 0xffffff);
	//rotatingGun.SetFrame(frame);
	//rotatingGun.Draw(screen, 100, 100);
	//if (++frame == 36) frame = 0;
}

void Game::MouseDown(int button)
{
	for (auto& element : LoadedLevel->uiContainer->Elements)
	{
		element.get()->OnMouseDown();
	}
}

void Game::MouseMove(int x, int y, int Ax, int Ay)
{
	LoadedLevel->LOL = ("X: " + std::to_string(x)) + (" Y: " + std::to_string(y));
	for (auto& element : LoadedLevel->uiContainer->Elements)
	{
		element.get()->OnMouseMove(x, y);
	}
}
