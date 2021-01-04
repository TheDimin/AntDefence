#pragma once
#include "UIElement.h"

class UIButton : public UIElement, public IText
{
public:
	StyleInfo styleInfo = StyleInfo();
private:
	std::function<void()> OnClickPtr = nullptr;
	std::function<bool()> IsActiveLambda = nullptr;
public:
	UIButton* SetStyle(StyleInfo& styleInfo);
	UIButton* SetOnClick(std::function<void()> function);
	UIButton* SetIsActiveLambda(std::function<bool()> function);
protected:
	void Render(class Tmpl8::Surface* surface) override;
	void OnBeginHover() override;
	void OnClick() override;
	void OnEndHover() override;
	virtual bool IsActive() override;
};
