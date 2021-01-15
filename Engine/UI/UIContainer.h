#pragma once
#include "UIElement.h"

#define GenerateWrapperFunction(FuncName,returnType,paramType,paramName)	\
	void FuncName(paramType paramName) override{							\
	for (auto& element : Elements){											\
		element->FuncName(paramName);}										\
	}

#define GenerateWrapperFunctionWithLambdaCheck(FuncName,returnType,paramType,paramName)	\
	void FuncName(paramType paramName) override{							\
	if (IsHiddenLambda != nullptr && IsHiddenLambda())						\
		return;																\
	for (auto& element : Elements){											\
		element->FuncName(paramName);}										\
	}

class UiContainer : public UIElement
{
public:
	UiContainer(int xPos, int yPos, int width, int height);
	UiContainer(vec2 pos, int width, int height);
	~UiContainer()  override = default;

protected:
	friend class Game;
	friend class Mob;
	std::function<bool()> IsHiddenLambda = nullptr;
public:
	void Render(Tmpl8::Surface* surface) override;
	class UIButton* Button(int xPos, int yPos, int xScale, int yScale);
	class UIButton* Button(int xPos, int yPos, int width, int height, std::string* textPtr);
	class UIText* Text(int xPos, int yPos, int width, std::string* textPtr);
	class UIText* Text(int xPos, int yPos, int size, std::string textPtr);
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
	void OnMouseDown() override;
	//GenerateWrapperFunction(OnMouseMove,Tmpl8::vec2&, pos)
	GenerateWrapperFunctionWithLambdaCheck(OnClick);
	GenerateWrapperFunction(OnEndHover);


public:
	int GetHeight()const;
	int GetWidth() const;
private:
	Pixel backgroundColor = 0x00000;
	friend class Level;
	std::vector<std::unique_ptr<UIElement>> Elements;
	//std::vector<IRenderable*> ActiveRenders;//TODO: use this to allow elements to be deactivated
	std::unique_ptr<Tmpl8::Surface> surface;
};
