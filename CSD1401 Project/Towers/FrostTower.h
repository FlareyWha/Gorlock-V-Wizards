/*!
@file       FrostTower.h
@author     Bay Yeok Hao (yeokhao.bay)
@brief		Contains declarations of functions, overrides and variables used by FrostTower
*//*_______________________________________________________________________*/

#pragma once
#include "BaseTower.h"
#include "../Projectiles/BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"

class FrostTower : public BaseTower
{
public:
	// Constructor & Deconstructor
	FrostTower(CP_Vector position);
	~FrostTower();

	// Update is overriden since FrostTower needs to draw the beam between the enemy and itself every frame
	void Update() override;

	// Attack is overriden to spawn IceProjectile that slows enemies on hit
	BaseProjectile* Attack(BaseEnemy* enemy) override;

	// TrackEnemy is called every game update to have the beam follow the current enemy
	void TrackEnemy(std::vector<BaseEnemy*>& enemyList);

	// technically this shouldnt be public but nuh uh not refactoring
	BaseEnemy* trackedEnemy;

	float beamLength = 0.f;
	float beamAngle = 0.f;

	bool withinRange = false;
};
