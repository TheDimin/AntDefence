#include <utility>

#include "Engine/UI/UIModal.h"


#include "Engine/UI/UiButton.h"
#include "Engine/UI/UIText.h"


UIModal::UIModal(Surface* TSurface)
{
	Elements = std::vector<std::unique_ptr<UIElement>>();
	UiContainer::Init(vec2(TSurface->GetWidth() * 0.20f, TSurface->GetHeight() * 0.35f), vec2(TSurface->GetWidth() * 0.6f, TSurface->GetHeight() * 0.25f), vec2(0, 0));

	SetBackGroundColor(0x808080);
	
	uiText = Text(surface->GetWidth()*0.5f, 50, 4, "Game Over");
	uiText->SetTextCentert(true);

	const std::function<bool()> Hidden = []() {return true; };

	CancelButton = Button(surface->GetWidth() - 90, surface->GetHeight() - 40, 75, 25);
	CancelButton->SetIsHiddenLambda(Hidden);
	CancelButton->SetText(&CancelText);

	AcceptButton = Button(surface->GetWidth() - (180 + 80), surface->GetHeight() - 40, 75, 25);
	AcceptButton->SetIsHiddenLambda(Hidden);
	AcceptButton->SetText(&AcceptText);

	OptionalButton = Button(surface->GetWidth() - (180 + 180 + 70), surface->GetHeight() - 40, 75, 25);
	OptionalButton->SetIsHiddenLambda(Hidden);
}

UIModal* UIModal::SetMessage(std::string Text)
{
	message = Text;
	//uiText->SetText(message);
	return this;
}

UIModal* UIModal::SetCancelText(std::string Text)
{
	CancelText = Text;
	CancelButton->SetText(&CancelText);
	return this;
}

UIModal* UIModal::SetAcceptText(std::string Text)
{
	AcceptText = Text;
	AcceptButton->SetText(&AcceptText);
	return this;
}

UIModal* UIModal::SetOptionalText(std::string Text)
{
	OptionalText = Text;
	OptionalButton->SetText(&OptionalText);
	return this;
}

UIModal* UIModal::SetOnCancel(std::function<void()> function)
{
	//Resharper hinted me to use std::move
	// I know we can't pass the value by reference because it would make the api weird
	OnCancel = std::move(function);
	CancelButton->SetIsHiddenLambda([]() {return false; });
	CancelButton->SetOnClick(OnCancel);
	return this;
}

UIModal* UIModal::SetOnAccept(std::function<void()> function)
{
	OnAccept = std::move(function);
	AcceptButton->SetIsHiddenLambda([]() {return false; });
	AcceptButton->SetOnClick(OnAccept);
	return this;
}

UIModal* UIModal::SetOnOptional(std::function<void()> function)
{
	OnOptional = std::move(function);
	OptionalButton->SetIsHiddenLambda([]() {return false; });
	OptionalButton->SetOnClick(OnOptional);
	return this;
}
