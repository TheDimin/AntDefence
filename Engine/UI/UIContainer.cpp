#include "UIContainer.h"
#include "UiButton.h"
#include "UIText.h"

UiContainer::UiContainer(Game* game, int width, int height)
{
	this->game = game;
	Elements = std::vector<std::unique_ptr<UIElement>>();
	surface = std::make_shared<Tmpl8::Surface>(width, height);
}

void UiContainer::Tick()
{
	surface->Clear(0x00000);
	for (std::unique_ptr<class UIElement>& element : Elements)
	{
		element->Render(surface.get());
	}
}

UIButton* UiContainer::Button(int xPos, int yPos, int xScale, int yScale)
{
	UIButton* uiElement = new UIButton();
	uiElement->Init(
		Tmpl8::vec2(static_cast<float>(xPos), static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(xScale), static_cast<float>(yScale)),
		Tmpl8::vec2((float)EngineGlobal::GetWidth() - surface->GetWidth(), (float)EngineGlobal::GetHeight() - surface->GetHeight())
	);

	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}

UIButton* UiContainer::Button(int xPos, int yPos, int width, int height, std::string* textPtr)
{
	UIButton* button = Button(xPos, yPos, width, height);
	button->styleInfo = StyleInfo();
	button->SetText(textPtr);
	return button;
}

UIText* UiContainer::Text(int xPos, int yPos, std::string* textPtr)
{
	UIText* uiElement = new UIText();
	uiElement->SetText(textPtr);
	uiElement->Init(
		Tmpl8::vec2((float)xPos, static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(1), static_cast<float>(1)),
		Tmpl8::vec2((float)EngineGlobal::GetWidth() - surface->GetWidth(), (float)EngineGlobal::GetHeight() - surface->GetHeight())
	);
	
	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}

UIText* UiContainer::Text(int xPos, int yPos, std::string textPtr)
{
	UIText* uiElement = new UIText();
	uiElement->SetText(textPtr);
	uiElement->Init(
		Tmpl8::vec2((float)xPos, static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(1), static_cast<float>(1)),
		Tmpl8::vec2((float)EngineGlobal::GetWidth() - surface->GetWidth(), (float)EngineGlobal::GetHeight() - surface->GetHeight())
	);

	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}
