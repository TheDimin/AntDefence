#include "UIText.h"

UIText::~UIText()
{
	if (isTextOwner)
		delete this->text;
}

UIText* UIText::SetText(std::string* text)
{
	if (isTextOwner)
		delete this->text;

	this->text = text;
	isTextOwner = false;
	return this;
}

UIText* UIText::SetText(std::string& text)
{
	if (isTextOwner)
		delete this->text;

	this->text = new std::string(text);
	isTextOwner = true;
	return this;
}

void UIText::Render(Tmpl8::Surface* surface)
{
	if (CenterText)
		if (text != nullptr)
			surface->Centre(const_cast<char*>(text->c_str()), static_cast<int>(Pos.x), static_cast<int>(Pos.y), (int)Scale.x, Color);
		else
			surface->Centre(const_cast<char*>("Unknown text"), static_cast<int>(Pos.x), static_cast<int>(Pos.y), (int)Scale.x, Color);
	else
		surface->Print(const_cast<char*>(text->c_str()), (int)Pos.x, (int)Pos.y, (int)Scale.x, Color);
}

void UIText::OnBeginHover()
{
}

void UIText::OnLeftMouseDown()
{
}

void UIText::OnEndHover()
{
}
