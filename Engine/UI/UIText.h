#pragma once
#include "UIElement.h"

class UIText :public UIElement
{
	~UIText();

public:
	UIText* SetText(std::string* text);
	UIText* SetText(std::string& text);
	UIText* SetTextCentert(bool centerText)
	{
		this->CenterText = centerText;
		return this;
	}
	UIText* SetColor(Pixel color)
	{
		this->Color = color;
		return this;
	}
	void Render(class Tmpl8::Surface* surface) override;
protected:
	void OnBeginHover() override;
	void OnLeftMouseDown() override;
	void OnEndHover() override;
	bool IsOverlapping(Tmpl8::vec2 pos) override { return false; }
private:
	Pixel Color = 0xfffffff;
	bool isTextOwner = false;
	std::string* text = nullptr;
	bool CenterText = true;
};

