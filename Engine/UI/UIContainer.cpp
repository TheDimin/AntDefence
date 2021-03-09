#include "UIContainer.h"
#include "UiButton.h"
#include "UIImage.h"
#include "UIModal.h"
#include "UIText.h"

UiContainer::UiContainer(int xPos, int yPos, int width, int height, int xOffset, int yOffset)
{
	Elements = std::vector<std::unique_ptr<UIElement>>();
	UiContainer::Init(vec2(xPos, yPos), vec2(width, height), vec2(xOffset, yOffset));
}

void UiContainer::Init(vec2 pos, vec2 scale, vec2 offset)
{
	IsHovering = true;
	UIElement::Init(pos, scale, offset);
	surface = std::make_unique< Tmpl8::Surface >((int)scale.x, (int)scale.y);
	surface->InitCharset();
}

UiContainer::~UiContainer()
{
	surface.reset();
	Elements.clear();
	delete modalInstance;
}


void UiContainer::Render(Tmpl8::Surface* screen)
{
	if (IsHiddenLambda != nullptr && IsHiddenLambda())
		return;

	surface->Clear(backgroundColor);
	for (std::unique_ptr<class UIElement>& element : Elements)
	{
		element->Render(this->surface.get());
	}

	this->surface->CopyTo(screen, (int)Pos.x, (int)Pos.y);
}

UIButton* UiContainer::Button(int xPos, int yPos, int xScale, int yScale)
{
	UIButton* uiElement = new UIButton();
	uiElement->Init(
		Tmpl8::vec2(static_cast<float>(xPos), static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(xScale), static_cast<float>(yScale)),
		Pos + Offset
	);

	Elements.insert(end(Elements), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}

UIButton* UiContainer::Button(int xPos, int yPos, int width, int height, std::string* textPtr)
{
	UIButton* button = Button(xPos, yPos, width, height);
	button->styleInfo = StyleInfo();
	button->SetText(textPtr);
	return button;
}

UIImage* UiContainer::Image(int xPos, int yPos, int width, int height, Sprite* sprite)
{
	UIImage* image = new UIImage();
	image->Init(
		Tmpl8::vec2((float)xPos, static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(width), static_cast<float>(height)),
		Pos
	);
	image->SetSprite(sprite);
	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(image));
	return image;
}

UIText* UiContainer::Text(int xPos, int yPos, int width, std::string* textPtr)
{
	UIText* uiElement = new UIText();
	uiElement->SetText(textPtr);
	uiElement->Init(
		Tmpl8::vec2((float)xPos, static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(width), static_cast<float>(1)),
		Pos
	);

	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}

UIText* UiContainer::Text(int xPos, int yPos, int size, std::string textPtr)
{
	UIText* uiElement = new UIText();
	uiElement->SetText(textPtr);
	uiElement->Init(
		Tmpl8::vec2((float)xPos, static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(size), static_cast<float>(1)),
		Pos
	);

	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}

UIModal* UiContainer::Modal(std::string message)
{
	if (modalInstance == nullptr) {
		UIModal* modal = new UIModal(surface.get());
		Elements.insert(end(Elements), std::unique_ptr<UIElement>(modal));
		modalInstance = modal;
	}

	modalInstance->SetMessage(message);
	return modalInstance;
}

UiContainer* UiContainer::Container(int xPos, int yPos, int width, int height)
{
	return Container(vec2(xPos, yPos), vec2(width, height));
}

UiContainer* UiContainer::Container(vec2 pos, vec2 size)
{
	UiContainer* uiElement = new UiContainer(pos, size, this->Pos);
	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}



bool UiContainer::OnMouseMove(Tmpl8::vec2 mousePos)
{
	for (auto& element : Elements)
	{
		UIElement* elem = element.get();
		if (elem->OnMouseMove(mousePos))
			return true;
	}
	return false;
}

bool UiContainer::OnLeftClick()
{
	if (IsHiddenLambda != nullptr && IsHiddenLambda() || !IsActive())
		return false;

	for (auto& element : Elements)
	{
		if (element->OnLeftClick())
			return true;
	}
	return false;
}

int UiContainer::GetWidth() const
{
	return surface->GetWidth();
}

int UiContainer::GetHeight() const
{
	return surface->GetHeight();
}
