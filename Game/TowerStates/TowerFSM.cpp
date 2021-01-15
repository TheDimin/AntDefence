#include "TowerFSM.h"

#include "../Tower.h"

void TowerFSM::Render(Tmpl8::Surface* surface)
{
	FSM::Render(surface);
#if _DEBUG	
	surface->InitCharset();
	//https://stackoverflow.com/questions/3649278/how-can-i-get-the-class-name-from-a-c-object
	if (tower != nullptr && activeState != nullptr)
	{
		surface->Centre(const_cast<char*>(typeid(*activeState).name()), (int)tower->GetLocation().x, (int)tower->GetLocation().y, 0xfffffff);
	}
#endif
}
