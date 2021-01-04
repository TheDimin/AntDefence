#include "GameObject.h"
#include <iostream>
#include <string>
#include "EngineGlobal.h"

void GameObject::OnLoad()
{
	std::cout<< "gameObject loaded" <<Name<< std::endl;
}