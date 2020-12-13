#pragma once
#include "UIElement.h"


class UiContainer : public ITickable
{
public:
	UiContainer(Game* game, int width, int height);
	~UiContainer() = default;

protected:
	friend class Game;
	void Tick() override;
public:
	class UIButton* Button(int xPos, int yPos, int xScale, int yScale);
	class UIButton* Button(int xPos, int yPos, int width, int height, std::string* textPtr);

private:
	friend class Level;
	std::vector<std::unique_ptr<UIElement>> Elements ;
	Game* game;
	std::shared_ptr<Tmpl8::Surface> surface;
};
