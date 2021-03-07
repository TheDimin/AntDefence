#pragma once
#include "UIElement.h"
class UIImage :
	public UIElement
{
public:
	void Render(Tmpl8::Surface* surface) override;
	UIImage* SetSprite(Sprite* sprite);


protected:
	bool IsOverlapping(Tmpl8::vec2 pos) override;
private:
	Sprite* Sprite = nullptr;
};

