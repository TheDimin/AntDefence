#include "UIImage.h"

void UIImage::Render(Tmpl8::Surface* surface)
{
	Sprite->DrawScaled((int)Pos.x, (int)Pos.y, (int)Scale.x, (int)Scale.y, surface);
}

UIImage* UIImage::SetSprite(Tmpl8::Sprite* sprite)
{
	Sprite = sprite;
	return this;
}

bool UIImage::IsOverlapping(Tmpl8::vec2 pos)
{
	return false;
}
