#include "TowerAtackingState.h"
#include "TowerFSM.h"
#include "../GameLevel.h"
#include "../Tower.h"
#include "../Events/TargetFoundEvent.h"
#include "../Events/TargetLostEvent.h"
#include <cmath>

void TowerAtackingState::OnStateEnter(Event* e)
{
	TargetFoundEvent* eTarget = dynamic_cast<TargetFoundEvent*>(e);
	TargetMob = eTarget->mob;
	mobData = eTarget->mob->mobData;
#if STATE_DEBUG
	printf("[TowerAtackingState] OnStateEnter \n");
#endif
	TickCooldown = tower->towerData->FindStat(2)->amount * 50;
	attacked = 0;
}

void TowerAtackingState::OnStateExit(Event* newEvent)
{
	TargetMob = nullptr;
	mobData = nullptr;
}

//https://love2d.org/forums/viewtopic.php?t=83180
float lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

void TowerAtackingState::Tick(float deltaTime)
{
	if (!tower->gLVL->IsValid(TargetMob))
	{
		tower->towerFSM->InvokeEvent(new TargetLostEvent());
		return;
	}

	if (attacked > 0)
	{
		attacked -= deltaTime;
	}

	tower->rotation = (int)lerp((float)tower->rotation, (atan2((tower->GetLocation() - TargetMob->GetLocation()).x, (tower->GetLocation() - TargetMob->GetLocation()).y)) * 180.0f / PI, 10.0f * (deltaTime / 1000.0f));

	const auto xDistance = abs(TargetMob->GetLocation().x - tower->GetLocation().x);
	const auto yDistance = abs(TargetMob->GetLocation().y - tower->GetLocation().y);

	const float xMaxDistance = ((tower->towerData->range + 2) * (gLVL->CalculateTileWidth() * 0.5f));
	const float yMaxDistance = ((tower->towerData->range + 2) * (gLVL->CalculateTileHeight() * 0.5f));

	if (!(xDistance < xMaxDistance && yDistance < yMaxDistance))
		tower->towerFSM->InvokeEvent(new TargetLostEvent());

	TickCooldown -= deltaTime;
	if (TickCooldown > 0) return;

	int amount = (int)tower->towerData->FindStat(1)->amount;
	tower->ShotTimer = tower->towerData->FindStat(2)->amount * 60;
	TickCooldown += tower->towerData->FindStat(2)->amount * 100;

	if (TargetMob->TakeDamage(amount))
	{
		gLVL->AddMoney(mobData->moneyOnKill);
		tower->towerFSM->InvokeEvent(new TargetLostEvent());
		return;
	}
	attacked = tower->towerData->FindStat(2)->amount * 40;
}

void TowerAtackingState::OnLeftClick(Tmpl8::vec2& mousePos)
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
		surface->Print("ATTACKING", (int)tower->GetLocation().x, (int)tower->GetLocation().y + 10, 0xfffffff);
#endif

	if (attacked > 0)
	{
		Sprite* sprite = tower->towerData->asset.get();
		sprite->SetFrame(3);

		float hitSize = lerp(0.01f, 0.8f, 0.5f * sin(attacked / (tower->towerData->FindStat(2)->amount * 60)) + 0.5f);
		vec2 loc = TargetMob->GetLocation() - TargetMob->GetSize() * (hitSize / 2.0f);



		sprite->DrawScaled((int)loc.x, (int)loc.y, (int)(hitSize * TargetMob->GetSize().x), (int)(hitSize * TargetMob->GetSize().y), surface);
	}
}
