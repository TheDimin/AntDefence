#include <utility>
#include "UIModal.h"
#include "UiButton.h"
#include "UIText.h"


const std::function<bool()> UnHide = []() {return false; };
const std::function<bool()> Hide = []() {return true; };

UIModal::UIModal(Surface* TSurface)
{
	Elements = std::vector<std::unique_ptr<UIElement>>();
	UiContainer::Init(vec2(TSurface->GetWidth() * 0.20f, TSurface->GetHeight() * 0.35f), vec2(TSurface->GetWidth() * 0.6f, TSurface->GetHeight() * 0.25f), vec2(0, 0));

	SetBackGroundColor(0x808080);

	uiText = Text((int)(surface->GetWidth() * 0.5f), 35, 4, "Modal Text");
	uiText->SetTextCentert(true);

	CancelButton = Button(surface->GetWidth() - 90, surface->GetHeight() - 40, 75, 25);
	CancelButton->SetIsHiddenLambda(Hide);
	CancelButton->SetText(&CancelText);

	AcceptButton = Button(surface->GetWidth() - (180 + 80), surface->GetHeight() - 40, 75, 25);
	AcceptButton->SetIsHiddenLambda(Hide);
	AcceptButton->SetText(&AcceptText);

	OptionalButton = Button(surface->GetWidth() - (180 + 180 + 70), surface->GetHeight() - 40, 75, 25);
	OptionalButton->SetIsHiddenLambda(Hide);
}

UIModal* UIModal::Get(Surface* screen)
{
	if (instance == nullptr)
	{
		instance = new UIModal(screen);
	}

	return instance;
}

UIModal* UIModal::SetMessage(std::string Text)
{
	message = Text;
	uiText->SetText(message);
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
	OnCancel = function;
	CancelButton->SetIsHiddenLambda(OnCancel == nullptr ? Hide : UnHide);
	CancelButton->SetOnClick(OnCancel);
	return this;
}

UIModal* UIModal::SetOnAccept(std::function<void()> function)
{
	OnAccept = function;
	AcceptButton->SetIsHiddenLambda(OnAccept == nullptr ? Hide : UnHide);
	AcceptButton->SetOnClick(OnAccept);
	return this;
}

UIModal* UIModal::SetOnOptional(std::function<void()> function)
{
	OnOptional = std::move(function);
	OptionalButton->SetIsHiddenLambda(OnOptional == nullptr ? Hide : UnHide);
	OptionalButton->SetOnClick(OnOptional);
	return this;
}

void UIModal::OnButtonClicked()
{
	PendingKill = true;
}

void UIModal::Render(Tmpl8::Surface* surface)
{
	if (PendingKill)
	{
		delete this;
		return;
	}
	UiContainer::Render(surface);
}
