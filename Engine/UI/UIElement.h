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
public:
	vec2 getScale() const { return Scale; }

protected:
	vec2 Pos;
	vec2 Scale;
	vec2 Offset;
	vec4 BoundingBox;
	vec4 LocalBoundingBox;
private:
	friend class Level;
	friend class UiContainer;
	bool inline Overlaps(vec2& mousePos);

protected:
	bool IsOverlapping(Tmpl8::vec2 pos) override;
	virtual bool IsActive();
	virtual void Init(vec2 Pos, vec2 Scale, vec2 Offset);

protected://Not all ui elements implement these
	friend class Level;
	void OnClick() override {}
	void OnBeginHover() override {}
	void OnEndHover() override {}
	
};

