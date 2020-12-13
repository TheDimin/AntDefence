#pragma once
#include "EngineGlobal.h"
#include "template.h"
#include "UIHelpers.h"
class Game;
using namespace Tmpl8;

class UIElement : public IMouseEvent, public IRenderable
{
protected:
	vec2 Pos;
	vec2 Scale;

	bool Enabled() override;
private:
	friend class Level;
	friend class UiContainer;
	void Init(vec2& Pos, vec2& Scale);
	bool inline Overlaps(vec2 mousePos);
	bool IsOverlapping(int x, int y) override;
};

