#pragma once
#include "UIContainer.h"
#include "UIElement.h"

class UIModal final :
	public UiContainer
{
public:
	UIModal(Surface* surface);
	~UIModal()
	{
		OnAccept = nullptr;
		OnCancel = nullptr;
		OnOptional = nullptr;
	};
	//Modals allow for singelton acces
	static UIModal* Get(Surface* screen);


	UIModal* SetMessage(std::string Text);
	UIModal* SetCancelText(std::string Text);
	UIModal* SetAcceptText(std::string Text);
	UIModal* SetOptionalText(std::string Text);


	UIModal* SetOnCancel(std::function<void()> function);
	UIModal* SetOnAccept(std::function<void()> function);
	UIModal* SetOnOptional(std::function<void()> function);
private:
	void OnButtonClicked();


public:
	void Render(Tmpl8::Surface* surface) override;
private:
	std::string message;
	std::string CancelText = "Cancel";
	std::string AcceptText = "Accept";
	std::string OptionalText;

	UIText* uiText = nullptr;
	UIButton* CancelButton = nullptr;
	UIButton* AcceptButton = nullptr;
	UIButton* OptionalButton = nullptr;

	std::function<void()> OnCancel;
	std::function<void()> OnAccept;
	std::function<void()> OnOptional;

	bool PendingKill = false;

	inline static UIModal* instance = nullptr;
};
