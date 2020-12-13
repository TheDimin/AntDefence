#pragma once
#include "EngineGlobal.h"
#include "Component.h"

class GameObject
{
	REFLECT_CLASS(GameObject)

		friend class Level;
	void OnLoad();

public:
	std::string Name = "GameObject";
	std::vector<std::unique_ptr<Component>> Components;
};