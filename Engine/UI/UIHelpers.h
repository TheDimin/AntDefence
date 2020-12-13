#pragma once
#include <string>

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
	virtual bool IsOverlapping(int x, int y) = 0;

private:
	friend class Game;
	bool OnMouseMove(int x, int y);
	void OnMouseDown();
};

class IText
{
protected:
	std::string* Text = nullptr;
public:
	void SetText(std::string* textPTR);
	std::string* GetText();
};