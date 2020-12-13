#pragma once
#include "UIElement.h"

class UIButton : public UIElement, public IText
{
protected:
	void Render(class Tmpl8::Surface* surface) override;
	void OnBeginHover() override;
	void OnClick() override;
	void OnEndHover() override;
};
