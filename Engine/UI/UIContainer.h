#pragma once
#pragma once
#include "UIElement.h"

#define CallWrap(FuncName)								\
	void FuncName() override{							\
	for (auto& element : Elements){						\
		element->FuncName();}							\
	}

#define CallWrapChecked(FuncName)						\
	void FuncName() override{							\
	if (IsHiddenLambda != nullptr && IsHiddenLambda())	\
		return;											\
	for (auto& element : Elements){						\
		element->FuncName();}							\
	}

class UiContainer : public UIElement
{
public:
	UiContainer(int xPos, int yPos, int width, int height, int xOffset, int yOffset);
	UiContainer(vec2 pos, int width, int height) : UiContainer((int)pos.x, (int)pos.y, width, height, 0, 0) {};
	UiContainer(vec2 pos, vec2 size) : UiContainer((int)pos.x, (int)pos.y, (int)size.x, (int)size.y, 0, 0) {};
	UiContainer(vec2 pos, vec2 size, vec2 offset) : UiContainer((int)pos.x, (int)pos.y, (int)size.x, (int)size.y, (int)offset.x, (int)offset.y) {};
	UiContainer() = default;
	~UiContainer();

protected:
	friend class Game;
	friend class GameLevel;
	friend class Mob;
	std::function<bool()> IsHiddenLambda = nullptr;
public:
	void Render(Tmpl8::Surface* surface) override;
	class UIButton* Button(int xPos, int yPos, int xScale, int yScale);
	class UIButton* Button(int xPos, int yPos, int width, int height, std::string* textPtr);
	class UIImage* Image(int xPos, int yPos, int width, int height, Sprite* sprite);
	class UIText* Text(int xPos, int yPos, int width, std::string* textPtr);
	class UIText* Text(int xPos, int yPos, int size, std::string textPtr);
	class UIModal* Modal(std::string message);


public:
	UiContainer* Container(int xPos, int yPos, int width, int height);
	UiContainer* Container(vec2 pos, vec2 size);
	UiContainer* SetBackGroundColor(Pixel color)
	{
		backgroundColor = color;
		return this;
	}
	UiContainer* SetIsActiveLambda(std::function<bool()> lambda)
	{
		IsHiddenLambda = lambda;
		return this;
	}
protected:
	void Init(vec2 Pos, vec2 Scale, vec2 Offset) override;

	bool IsOverlapping(Tmpl8::vec2 pos) override
	{
		return true;
	}


	bool OnMouseMove(Tmpl8::vec2 pos) override;
	bool OnLeftClick() override;
	//GenerateWrapperFunction(OnMouseMove,Tmpl8::vec2&, pos)
	CallWrapChecked(OnLeftMouseDown);
	CallWrap(OnEndHover);


public:
	int GetHeight()const;
	int GetWidth() const;
protected:
	Pixel backgroundColor = 0x00000;
	friend class Level;
	std::vector<std::unique_ptr<UIElement>> Elements = std::vector<std::unique_ptr<UIElement>>();
	//std::vector<IRenderable*> ActiveRenders;//TODO: use this to allow elements to be deactivated
	std::unique_ptr<Tmpl8::Surface> surface;
	class UIModal* modalInstance = nullptr;
};