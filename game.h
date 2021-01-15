#pragma once
#include "surface.h"
#include "Engine/EngineGlobal.h"
#include "Engine/Level.h"
#include "Engine/LevelHelper.h"


class Game
{
public:
	~Game();
	void SetTarget(Tmpl8::Surface* surface) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button);
	void MouseMove(int x, int y, int Ax, int Ay);
	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { /* implement if you want to handle keys */ }
	Tmpl8::Surface* GetScreen() { return screen; }
private:
	Tmpl8::Surface* screen;
public:
	template<class LevelType>
	void SwitchLevel(std::string newLevel)
	{
		if (NewLevel != nullptr)
		{
			delete NewLevel;
			NewLevel = nullptr;
		}
		NewLevel = LevelHelper::Load<LevelType>(newLevel);
	}
private:
	Level* NewLevel = nullptr;
	class std::unique_ptr<Level> LoadedLevel;
	std::vector<IRenderable*> Renderables = std::vector<IRenderable*>();
};


