#pragma once
#include <string>

namespace Tmpl8 {
	class vec2;
}

class IMouseEvent
{
public:
	IMouseEvent() = default;
	virtual ~IMouseEvent() = default;
protected:
	bool IsHovering;
	virtual void OnClick() = 0;
	virtual void OnBeginHover() = 0;
	virtual void OnEndHover() = 0;
	virtual bool IsOverlapping(Tmpl8::vec2 pos) = 0;

	friend class Game;
	friend class Level;
	virtual bool OnMouseMove(Tmpl8::vec2 pos);
	virtual bool OnMouseDown();
};

class IText
{
protected:
	std::string* Text = nullptr;
public:
	void SetText(std::string* textPTR);
	std::string* GetText();
};