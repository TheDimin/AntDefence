#pragma once
#include "UIElement.h"

class UIText :public UIElement
{
	~UIText();

public:
	UIText* SetText(std::string* text);
	UIText* SetText(std::string& text);
	void Render(class Tmpl8::Surface* surface) override;
protected:
	void OnBeginHover() override;
	void OnClick() override;
	void OnEndHover() override;
private:
	bool isTextOwner = false;
	std::string* text = nullptr;
};

