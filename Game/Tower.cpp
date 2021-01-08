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

void Tower::SetLvl(Level* lvl)
{
	this->lvl = lvl;
	gLVL = dynamic_cast<GameLevel*>(lvl);

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