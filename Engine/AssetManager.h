#pragma once
#include <map>
#include <memory>
#include <string>
#include "../surface.h"


class AssetManager
{
public:
	void Load(std::string LevelName);

private:
		std::map<std::string, std::unique_ptr<Tmpl8::Sprite>> Assets;
};

