#include "GameObject.h"
#include <iostream>
#include <string>
#include "EngineGlobal.h"

BEGIN_REFLECT(GameObject)
PROPERTY_REFLECT(Name, std::string)
FINISH_REFLECT()


void GameObject::OnLoad()
{
	std::cout<< "gameObject loaded" <<Name<< std::endl;
}

