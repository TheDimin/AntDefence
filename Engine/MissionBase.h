#pragma once
#include <string>
class Level;

class MissionBase
{
	friend class Game;
protected:
	void Init();

	void LoadLevel(std::string path);





protected:
	Level* loadedLevel;
};

