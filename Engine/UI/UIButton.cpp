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
	{
#ifdef UI_DEBUG
		std::cout << "IS Hidden lambda returned true" << std::endl;
#endif
		return;
	}
	bool active = IsActive();
	if (styleInfo.Image != nullptr)
	{
		styleInfo.Image->SetFrame(styleInfo.SpriteIndex);
		styleInfo.Image->DrawScaledSub(
			static_cast<int>(Pos.x - Scale.x),
			static_cast<int>(Pos.y - Scale.y),
			static_cast<int>(Scale.x * 2),
			static_cast<int>(Scale.y * 2),
			!active ? styleInfo.Disabled : IsHovering ? styleInfo.Hover : styleInfo.normal, surface);
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
		char* str = const_cast<char*>(GetText()->c_str());
		surface->Centre(str, static_cast<int>(Pos.x), static_cast<int>(Pos.y), (int)floor((Scale.x * 2) / (6.0f * (int)strlen(str))), active ? 0xfffffff : styleInfo.Disabled);
	}

#ifdef UI_COLLISION_DEBUG
	//Draw on top
	EngineGlobal::GetDebugScreen()->Bar((int)BoundingBox.x, (int)BoundingBox.z, (int)BoundingBox.y, (int)BoundingBox.w, 0xFF0000);
#endif
}

void UIButton::OnBeginHover()
{
#ifdef UI_DEBUG
	std::cout << "HOVERING" << std::endl;
#endif
}

void UIButton::OnEndHover()
{
#ifdef UI_DEBUG
	std::cout << "END HOVERING" << std::endl;
#endif

}

bool UIButton::IsActive()
{
	if (IsActiveLambda == nullptr)
		return true;

	return IsActiveLambda();
}

void UIButton::OnLeftMouseDown()
{
#ifdef UI_DEBUG
	std::cout << "OnLeftMouseDown" << std::endl;
#endif

	if (OnClickPtr != nullptr)
		OnClickPtr();
}

