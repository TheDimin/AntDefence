#include "Tower.h"
#include "GameLevel.h"
#include "TowerStates/TowerFSM.h"
#include "TowerStates/TowerIdleState.h"
#include "Events/TargetFoundEvent.h"
#include "Events/TargetLostEvent.h"
#include "TowerStates/TowerAtackingState.h"

Tower::Tower(TowerData* towerData, Tmpl8::vec2 tile, Tmpl8::vec2 location, Tmpl8::vec2 size) : GameObject(towerData->asset.get(), location, size), tile(tile), towerData(towerData)
{
}

void Tower::SetLvl(Level* toSetLvl)
{
	this->lvl = toSetLvl;
	gLVL = dynamic_cast<GameLevel*>(toSetLvl);

	towerFSM = std::make_unique<TowerFSM>(this, gLVL);

	TowerIdleState* towerIdle = new TowerIdleState();
	TowerAtackingState* towerAttack = new TowerAtackingState();


	TowerTransition* idleToAttack = new TowerTransition(towerIdle, towerAttack, DefaultGuardCastCheck(TargetFoundEvent));

	TowerTransition* AttackToIdleTargetLost = new TowerTransition(towerAttack, towerIdle, DefaultGuardCastCheck(TargetLostEvent));
	//TowerTransition* AttackToIdleTargetKilled = new TowerTransition(towerAttack, towerIdle,DefaultGuardCastCheck(TargetLostEvent),[]);

	towerFSM->RegisterTransition(idleToAttack);
	towerFSM->RegisterTransition(AttackToIdleTargetLost);
	towerFSM->ActivateFsm(towerIdle);
}

void Tower::Tick(float deltaTime)
{
	GameObject::Tick(deltaTime);
	towerFSM->Tick(deltaTime);

	if (ShotTimer > 0)
		ShotTimer -= deltaTime;
}

void Tower::Render(Tmpl8::Surface* surface)
{
	sprite->SetFrame(0);
	sprite->DrawScaled((int)drawLocation.x, (int)drawLocation.y, (int)size.x, (int)size.y, surface);

	sprite->SetFrame(1);
	sprite->DrawScaled((int)drawLocation.x - 5, (int)drawLocation.y - 10, (int)size.x, (int)size.y, surface, rotation, vec2(+5, +10));

	towerFSM->Render(surface);
	if (ShotTimer > 0)
	{
		sprite->SetFrame(2);
		sprite->DrawScaled((int)drawLocation.x - 5, (int)drawLocation.y - 10, (int)size.x, (int)size.y, surface, rotation, vec2(+5, +10));
	}
}
