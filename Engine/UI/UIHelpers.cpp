#include "UIHelpers.h"
#include "UIElement.h"


bool IMouseEvent::OnMouseMove(int x, int y)
{
	bool overlaps = this->IsOverlapping(x, y);
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
