#include "UIButton.h"

#include <iostream>

UIButton* UIButton::SetStyle(StyleInfo& styleInfo)
{
	this->styleInfo = styleInfo;
	return this;
}

UIButton* UIButton::SetOnClick(std::function<void()> function)
{
	this->OnClickPtr = function;
	return this;
}

UIButton* UIButton::SetIsHiddenLambda(std::function<bool()> function)
{
	this->IsHiddenLambda = function;
	return this;
}


UIButton* UIButton::SetIsActiveLambda(std::function<bool()> function)
{
	this->IsActiveLambda = function;
	return this;
}

void UIButton::Render(Tmpl8::Surface* surface)
{
	if (IsHiddenLambda != nullptr && IsHiddenLambda())
		return;

	bool active = IsActive();
	if (styleInfo.Image != nullptr)
	{
		styleInfo.Image->SetFrame(styleInfo.SpriteIndex);
		styleInfo.Image->DrawScaled(static_cast<int>(Pos.x - Scale.x), static_cast<int>(Pos.y - Scale.y), static_cast<int>(Scale.x * 2), static_cast<int>(Scale.y * 2), !active ? styleInfo.Disabled : IsHovering ? styleInfo.Hover : styleInfo.normal, surface);
		//surface->
	}
	else
		surface->Bar(
			static_cast<int>(LocalBoundingBox.x),
			static_cast<int>(LocalBoundingBox.z),
			static_cast<int>(LocalBoundingBox.y),
			static_cast<int>(LocalBoundingBox.w),
			IsHovering ? styleInfo.Hover : styleInfo.normal);
	if (Text != nullptr)
	{
		surface->Centre(const_cast<char*>(GetText()->c_str()), static_cast<int>(Pos.x), static_cast<int>(Pos.y), 2, active ? 0xfffffff : styleInfo.Disabled);
	}
}

void UIButton::OnBeginHover()
{
	std::cout << "HOVERING" << std::endl;
}

void UIButton::OnEndHover()
{
	std::cout << "END HOVERING" << std::endl;
}

bool UIButton::IsActive()
{
	if (IsActiveLambda == nullptr)
		return true;

	return IsActiveLambda();
}

void UIButton::OnClick()
{
	if (OnClickPtr != nullptr)
		try
	{
		OnClickPtr();
	}
	catch (std::exception e)
	{
		std::cout << "OnClick Failed " << e.what() << std::endl;
	}
}

