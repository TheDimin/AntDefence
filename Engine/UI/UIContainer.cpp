#include "UIContainer.h"

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
	uiElement->Init(Tmpl8::vec2(static_cast<float>(xPos), static_cast<float>(yPos)), Tmpl8::vec2(static_cast<float>(xScale), static_cast<float>(yScale)));
	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return new UIButton();
}

UIButton* UiContainer::Button(int xPos, int yPos, int width, int height, std::string* textPtr)
{
	UIButton* button = Button(xPos, yPos, width, height);

	button->SetText(textPtr);
	return button;

}