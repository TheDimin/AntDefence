#pragma once
#include "UIHelpers.h"
#include "../EngineGlobal.h"
#include "../../template.h"

class Game;
using namespace Tmpl8;

struct StyleInfo
{
public:
	Pixel normal = 0x22222222;
	Pixel Hover = 0x33333333;
	Pixel Click = 0x11111111;
	Pixel Disabled = 0x0000000;
	Sprite* Image = nullptr;
	int SpriteIndex = 0;
};

class UIElement : public IMouseEvent, public IRenderable
{
protected:
	vec2 Pos;
	vec2 Scale;
	vec2 Offset;
	vec4 BoundingBox;
	vec4 LocalBoundingBox;
private:
	friend class Level;
	friend class UiContainer;
	void Init(vec2 Pos, vec2 Scale, vec2 Offset);
	bool inline Overlaps(vec2 mousePos);
	bool IsOverlapping(int x, int y) override;
protected:
	virtual bool IsActive();
};

