#include "UICredits.h"
#include "Engine/UI/UIText.h"

UICredits::UICredits(UiContainer* container)
{
	//Initialize the container
	UiContainer::Init(vec2(container->GetWidth() * 0.20f, container->GetHeight() * 0.35f), vec2(container->GetWidth() * 0.6f, container->GetHeight() * 0.25f), vec2(0, 0));

	SetBackGroundColor(0x808080);

	UIText* uiText = Text((int)(surface->GetWidth() * 0.5f), 35, 4, "Modal Text");
	uiText->SetTextCentert(true);


	container->RegisterElement(this);
}