#include "UIElement.h"
#include "surface.h"

bool UIElement::Enabled()
{
	return true;
}

void UIElement::Init(vec2& Pos, vec2& Scale)
{
	this->Pos = Pos;
	this->Scale = Scale;
}

bool UIElement::Overlaps(vec2 mousePos)
{
	return Pos.x + Scale.x <= mousePos.x && Pos.x - Scale.y >= mousePos.x && Pos.y + Scale.y <= mousePos.y && Pos.y - Scale.y >= mousePos.y;
}

bool UIElement::IsOverlapping(int x, int y)
{
	return Overlaps(vec2(x, y));
}

void UIButton::Render(Tmpl8::Surface* surface)
{
	surface->Bar(static_cast<int>(Pos.x - Scale.x), static_cast<int>(Pos.y - Scale.y), static_cast<int>(Pos.x + Scale.x), static_cast<int>(Pos.y + Scale.y), 0xFF0000);
	if (Text != nullptr)
	{
		surface->Print(const_cast<char*>(Text->c_str()), 0, 0, 0x000000);
	}
}

void UIButton::OnBeginHover()
{
}

void UIButton::OnClick()
{
}

void UIButton::OnEndHover()
{
}


