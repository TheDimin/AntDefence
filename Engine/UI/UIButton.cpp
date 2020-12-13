#include "UIButton.h"

#include <iostream>

void UIButton::Render(Tmpl8::Surface* surface)
{
	surface->Bar(LocalBoundingBox.x, LocalBoundingBox.z, LocalBoundingBox.y, LocalBoundingBox.w, IsHovering ? styleInfo.Hover : styleInfo.normal);
	if (GetText() != nullptr)
	{
		surface->Print(const_cast<char*>(GetText()->c_str()), Pos.x, Pos.y, 0xffffffff);
	}
	else
		std::cout << "TExt null ptr: " << (this) << std::endl;
}

void UIButton::OnBeginHover()
{
	std::cout << "HOVERING" << std::endl;
}

void UIButton::OnEndHover()
{
	std::cout << "END HOVERING" << std::endl;
}

void UIButton::OnClick()
{
	std::cout << "ITEM CLICKED" << std::endl;
}

