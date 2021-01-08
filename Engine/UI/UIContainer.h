#pragma once
#pragma once
#include "UIElement.h"


class UiContainer : public IRenderable
{
public:
	UiContainer(int xPos, int yPos, int width, int height);
	UiContainer(vec2* pos, int width, int height);
	~UiContainer();

protected:
	friend class Game;
	friend class Mob;

public:
	void Render(Tmpl8::Surface* surface) override;
	class UIButton* Button(int xPos, int yPos, int xScale, int yScale);
	class UIButton* Button(int xPos, int yPos, int width, int height, std::string* textPtr);
	class UIText* Text(int xPos, int yPos, std::string* textPtr);
	class UIText* Text(int xPos, int yPos, std::string textPtr);
	int GetHeight();
private:
	friend class Level;
	std::vector<std::unique_ptr<UIElement>> Elements;
	std::vector<IRenderable*> ActiveRenders;//TODO: use this to allow elements to be deactivated
	std::unique_ptr<Tmpl8::Surface> surface;
	vec2* pos = nullptr;
	bool owner = false;
};
