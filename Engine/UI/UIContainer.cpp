#include "UIContainer.h"
#include "UiButton.h"
#include "UIImage.h"
#include "UIText.h"

UiContainer::UiContainer(int xPos, int yPos, int width, int height)
{
	Elements = std::vector<std::unique_ptr<UIElement>>();
	surface = std::make_unique< Tmpl8::Surface >(width, height);
	UiContainer::Init(vec2(xPos, yPos), vec2(width, height), vec2(0, 0));
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
		Tmpl8::vec2((float)(0), (float)(EngineGlobal::GetHeight() - surface->GetHeight()))
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

UIImage* UiContainer::Image(int xPos, int yPos, int width, int height, Sprite* sprite)
{
	UIImage* image = new UIImage();
	image->Init(
		Tmpl8::vec2((float)xPos, static_cast<float>(yPos)),
		Tmpl8::vec2(static_cast<float>(width), static_cast<float>(height)),
		Tmpl8::vec2((float)EngineGlobal::GetWidth() - surface->GetWidth(), (float)EngineGlobal::GetHeight() - surface->GetHeight())
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
		Tmpl8::vec2((float)EngineGlobal::GetWidth() - surface->GetWidth(), (float)EngineGlobal::GetHeight() - surface->GetHeight())
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
		Tmpl8::vec2((float)EngineGlobal::GetWidth() - surface->GetWidth(), (float)EngineGlobal::GetHeight() - surface->GetHeight())
	);

	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}

UiContainer* UiContainer::Container(int xPos, int yPos, int width, int height)
{
	return Container(vec2(xPos, yPos), vec2(width, height));
}

UiContainer* UiContainer::Container(vec2 pos, vec2 size)
{
	UiContainer* uiElement = new UiContainer(pos, size);
	Elements.insert(Elements.begin(), std::unique_ptr<UIElement>(uiElement));
	return uiElement;
}

void UiContainer::Init(vec2 pos, vec2 scale, vec2 offset)
{
	IsHovering = true;
	UIElement::Init(pos, scale, offset);
	surface = std::make_unique< Tmpl8::Surface >((int)scale.x, (int)scale.y);
	surface->InitCharset();
}

bool UiContainer::OnMouseMove(Tmpl8::vec2 mousePos)
{
	for (auto& element : Elements)
	{
		if (element->OnMouseMove(mousePos))
			return true;
	}
	return false;
}

void UiContainer::OnMouseDown()
{
	if (IsHiddenLambda != nullptr && IsHiddenLambda() || !IsActive())
		return;

	for (auto& element : Elements)
	{
		element->OnMouseDown();
	}
}

int UiContainer::GetWidth() const
{
	return surface->GetWidth();
}

int UiContainer::GetHeight() const
{
	return surface->GetHeight();
}
