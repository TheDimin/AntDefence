#pragma once
#include "surface.h"
#include "Engine/EngineGlobal.h"
#include "Engine/Level.h"
#include "Engine/LevelHelper.h"


class Game
{
public:
	~Game();
	void SetTarget(Tmpl8::Surface* surface)
	{
		screen = surface;
		DebugSurface = std::make_unique<Surface>(surface->GetWidth(), surface->GetHeight());
		EngineGlobal::SetDebugScreen(DebugSurface.get());
	}
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button);
	void MouseMove(int x, int y, int Ax, int Ay);
	void KeyUp(int key) { /* implement if you want to handle keys */ }
	void KeyDown(int key);
	Tmpl8::Surface* GetScreen() { return screen; }
private:

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
	std::unique_ptr<Level> LoadedLevel = nullptr;
	std::unique_ptr<Tmpl8::Surface> DebugSurface = nullptr;
	Tmpl8::Surface* screen = nullptr;
};


