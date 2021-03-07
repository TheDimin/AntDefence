#include "PlayingState.h"

#include <iostream>


#include "../../surface.h"
#include "../../template.h"
#include "../../Engine/FSM/Event.h"

void PlayingState::OnStateEnter(Event* e)
{
#ifdef  STATE_DEBUG
	std::cout << "[PlayingState]: OnEnter" << std::endl;
#endif

}

void PlayingState::OnStateExit(Event* newEvent)
{
#ifdef  STATE_DEBUG
	std::cout << "[PlayingState]: OnExit" << std::endl;
#endif
}

void PlayingState::Tick(float deltaTime)
{

}

void PlayingState::Render(Tmpl8::Surface* surface)
{
}

void PlayingState::OnLeftClick(Tmpl8::vec2& mousePos)
{
#ifdef  STATE_DEBUG
	std::cout << "[PlayingState]: OnMouseDown" << std::endl;
#endif
}

void PlayingState::OnMouseMove(Tmpl8::vec2& mousePos)
{
}
