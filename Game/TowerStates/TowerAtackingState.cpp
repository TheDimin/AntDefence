#include "TowerAtackingState.h"
#include "TowerFSM.h"
#include "../GameLevel.h"
#include "../Tower.h"
#include "../Events/TargetFoundEvent.h"
#include "../Events/TargetLostEvent.h"

void TowerAtackingState::OnStateEnter(Event* e)
{
	TargetFoundEvent* eTarget = dynamic_cast<TargetFoundEvent*>(e);
	TargetMob = eTarget->mob;
	mobData = eTarget->mob->mobData;
	printf("[TowerAtackingState] OnStateEnter \n");
	TickCooldown = tower->towerData->FindStat(2)->amount*50;
}

void TowerAtackingState::OnStateExit(Event* newEvent)
{
	TargetMob = nullptr;
	mobData = nullptr;
}

void TowerAtackingState::Tick(float deltaTime)
{
	attacked = false;
	if (TargetMob == nullptr)
	{
		tower->towerFSM->InvokeEvent(new TargetLostEvent());
		return;
	}

	const auto xDistance = abs(TargetMob->GetLocation().x - tower->GetLocation().x);
	const auto yDistance = abs(TargetMob->GetLocation().y - tower->GetLocation().y);

	const float xMaxDistance = ((tower->towerData->range + 2) * (gLVL->CalculateTileWidth() * 0.5f));
	const float yMaxDistance = ((tower->towerData->range + 2) * (gLVL->CalculateTileHeight() * 0.5f));

	if (!(xDistance < xMaxDistance && yDistance < yMaxDistance))
		tower->towerFSM->InvokeEvent(new TargetLostEvent());

	TickCooldown -= deltaTime;
	if (TickCooldown > 0) return;


	printf("Attacking closest mob\n");
	int amount = (int)tower->towerData->FindStat(1)->amount;
	if (TargetMob->TakeDamage(amount))
	{
		gLVL->AddMoney(mobData->moneyOnKill);
		tower->towerFSM->InvokeEvent(new TargetLostEvent());
		return;
	}
	attacked = true;
	//rotation += 90;

	//if (rotation == 360)
		//rotation = 0;

	//printf("Apply dammage %d \n", rotation);
	TickCooldown += tower->towerData->FindStat(2)->amount*50;
}

void TowerAtackingState::OnMouseDown(Tmpl8::vec2& mousePos)
{
}

void TowerAtackingState::OnMouseMove(Tmpl8::vec2& mousePos)
{
}

void TowerAtackingState::Render(Tmpl8::Surface* surface)
{
#if _DEBUG
	surface->Line(tower->GetLocation().x, tower->GetLocation().y, TargetMob->GetLocation().x, TargetMob->GetLocation().y, 0xff0000);
	if (attacked)
		surface->Print("ATTACKING", tower->GetLocation().x, tower->GetLocation().y + 10, 0xfffffff);

#endif
}
