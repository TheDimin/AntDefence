#include "GameObject.h"
#include <iostream>
#include "EngineGlobal.h"
#include "Level.h"

void GameObject::OnLoad()
{
	std::cout << "gameObject loaded" << Name << std::endl;
}

void GameObject::Render(Tmpl8::Surface* surface)
{
	sprite->DrawScaled((int)drawLocation.x, (int)drawLocation.y, (int)size.x, (int)size.y, surface);
}

void GameObject::Destroy()
{
	if (pendingKill) return;
	pendingKill = true;
	lvl->DeleteObject(dynamic_cast<GameObject*>(this));
}
