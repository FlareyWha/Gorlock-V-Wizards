/*!
@file       StormTower.h
@author		Bay Yeok Hao (yeokhao.bay)
@brief		Contains declarations of functions, overrides and variables used by StormTower
*//*_______________________________________________________________________*/

#pragma once
#include "BaseTower.h"

class StormTower : public BaseTower
{
public:
	// Constructor & Deconstructor
	StormTower(CP_Vector position);
	~StormTower();
	// Update is overridden to render additional purple lightning beam that hits nearby enemy
	void Update() override;
	// Attack is overridden to spawn LightningProjectile that chains to nearby enemies
	BaseProjectile* Attack(BaseEnemy* enemy) override;

	float chainLength = 0.f, chainAngle = 0.f;
	bool enemyNearby = false;
};
