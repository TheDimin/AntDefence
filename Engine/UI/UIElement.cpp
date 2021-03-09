#include "UIElement.h"

void UIElement::Init(vec2 Pos, vec2 Scale, vec2 Offset)
{
	this->Pos = Pos;
	this->Scale = Scale;
	this->Offset = Offset;

	this->LocalBoundingBox = vec4(
		Pos.x - Scale.x,
		Pos.x + Scale.x,
		Pos.y - Scale.y,
		Pos.y + Scale.y
	);

	this->BoundingBox = vec4(
		Offset.x + Pos.x - Scale.x,
		Offset.x + Pos.x + Scale.x,
		Offset.y + Pos.y - Scale.y,
		Offset.y + Pos.y + Scale.y
	);
}

bool UIElement::IsOverlapping(Tmpl8::vec2 mousePos)
{
	return IsActive() ?
		BoundingBox.x <= mousePos.x &&
		BoundingBox.y >= mousePos.x &&
		BoundingBox.z <= mousePos.y &&
		BoundingBox.w >= mousePos.y :
		false;
}


bool UIElement::IsActive()
{
	return true;
}
