#pragma once
#include "UIHelpers.h"
#include "../EngineGlobal.h"
#include "../../template.h"

class Game;
using namespace Tmpl8;

struct StyleInfo
{
	Pixel normal = 0x55555555;
	Pixel Hover = 0x333333333;
	Pixel Click = 0x111111111;

};

class UIElement : public IMouseEvent, public IRenderable
{
protected:
	vec2 Pos;
	vec2 Scale;
	vec2 Offset;
	vec4 BoundingBox;
	vec4 LocalBoundingBox;
	bool Enabled() override;
private:
	friend class Level;
	friend class UiContainer;
	void Init(vec2& Pos, vec2& Scale, vec2 Offset);
	bool inline Overlaps(vec2 mousePos);
	bool IsOverlapping(int x, int y) override;
};

