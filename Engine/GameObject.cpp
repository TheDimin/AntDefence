#include "GameObject.h"
#include <iostream>
#include "EngineGlobal.h"
#include "Level.h"

void GameObject::OnLoad()
{
	std::cout << "gameObject loaded" << Name << std::endl;
}

void GameObject::Destroy()
{
	lvl->DeleteObject(this);
}
