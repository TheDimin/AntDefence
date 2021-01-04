#include "PlayingState.h"

#include <iostream>

#include "../../Engine/FSM/Event.h"

void PlayingState::OnStateEnter(Event* e)
{
	std::cout << "[PlayingState]: OnEnter" << std::endl;
}

void PlayingState::OnStateExit(Event* newEvent)
{
	std::cout << "[PlayingState]: OnExit" << std::endl;
}

void PlayingState::Update(float deltaTime)
{
	
}

void PlayingState::Draw(Tmpl8::Surface* surface)
{
}

void PlayingState::OnMouseDown(Tmpl8::vec2& mousePos)
{
	std::cout << "[PlayingState]: OnMouseDown" << std::endl;
}

void PlayingState::OnMouseMove(Tmpl8::vec2& mousePos)
{
}
