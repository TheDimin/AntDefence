#include "UIHelpers.h"
#include "UIElement.h"


bool IMouseEvent::OnMouseMove(Tmpl8::vec2 mousePos)
{
	bool overlaps = this->IsOverlapping(mousePos);
	if (overlaps != this->IsHovering)
	{
		if (overlaps)
			this->OnBeginHover();
		else
			this->OnEndHover();
		this->IsHovering = overlaps;
	}

	return overlaps;
}

void IMouseEvent::OnMouseDown()
{
	if (this->IsHovering)
		OnClick();
}

void IText::SetText(std::string* textPTR)
{
	Text = textPTR;
}

std::string* IText::GetText()
{
	return this->Text;
}
