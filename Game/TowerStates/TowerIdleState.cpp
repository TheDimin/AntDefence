#include "TowerIdleState.h"


#include "TowerFSM.h"
#include "../GameLevel.h"
#include "../Mob.h"
#include "../Tower.h"
#include "../Events/TargetFoundEvent.h"

void TowerIdleState::OnStateEnter(Event* e)
{
}

void TowerIdleState::OnStateExit(Event* newEvent)
{
}

void TowerIdleState::Tick(float deltaTime)
{
	if (gLVL->activeMobCount > 0)
	{

		TickCooldown -= deltaTime;
		if (TickCooldown > 0)
			return;
		TickCooldown = tower->towerData->FindStat(2)->amount * 100;


		Mob* ClosestMob = nullptr;
		float distance = 9999999999999999999999.0f;

		float xMaxDistance = ((tower->towerData->range + 2) * (gLVL->CalculateTileWidth() * 0.5f));
		float yMaxDistance = ((tower->towerData->range + 2) * (gLVL->CalculateTileHeight() * 0.5f));

		for (auto* mob : gLVL->activeMobs)
		{
			auto xDistance = abs(mob->GetLocation().x - tower->GetLocation().x);
			auto yDistance = abs(mob->GetLocation().y - tower->GetLocation().y);

			if (xDistance < xMaxDistance && yDistance < yMaxDistance) {
				if (xDistance + yDistance < distance)
				{
					distance = xDistance + yDistance;
					ClosestMob = mob;
				}
			}
		}

		if (ClosestMob != nullptr)
		{
			tower->towerFSM->InvokeEvent(new TargetFoundEvent(ClosestMob));
		}
	}
}

void TowerIdleState::OnMouseDown(Tmpl8::vec2& mousePos)
{
}

void TowerIdleState::OnMouseMove(Tmpl8::vec2& mousePos)
{
}

void TowerIdleState::Render(Tmpl8::Surface* surface)
{
}
