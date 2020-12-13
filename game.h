#pragma once
#include <memory>

#include "surface.h"
#include "Engine/Level.h"
#include "Engine/FSM/FSM.h"


class Game
{
public:
	void SetTarget(Tmpl8::Surface* surface) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { /* implement if you want to detect mouse movement */ }
	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { /* implement if you want to handle keys */ }
	Tmpl8::Surface* GetScreen() { return screen; }
private:
	Tmpl8::Surface* screen;
	FSM* gameState;

private:
	std::unique_ptr< Level> LoadedLevel;
	std::vector<IRenderable*> Renderables = std::vector<IRenderable*>();
};


