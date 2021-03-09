#pragma once
#include "UIElement.h"

class UIButton : public UIElement, public IText
{
public:
	StyleInfo styleInfo = StyleInfo();
private:
	std::function<void()> OnClickPtr = nullptr;
	std::function<bool()> IsActiveLambda = nullptr;
	std::function<bool()> IsHiddenLambda = nullptr;
public:
	UIButton* SetStyle(StyleInfo& styleInfo);
	UIButton* SetOnClick(std::function<void()> function);
	UIButton* SetIsHiddenLambda(std::function<bool()> function);
	UIButton* SetIsActiveLambda(std::function<bool()> function);
public:
	void Render(class Tmpl8::Surface* surface) override;
protected:
	void OnBeginHover() override;
	void OnLeftMouseDown() override;
	void OnEndHover() override;
	virtual bool IsActive() override;
};
