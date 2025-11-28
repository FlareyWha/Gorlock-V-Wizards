/*!
@file       LightningTower.h
@author		Chew Zavier(c.zavier)
@brief		Contains declarations of functions, overrides and variables used by LightningTower
*//*_______________________________________________________________________*/

#pragma once
#include "BaseTower.h"
class LightningTower : public BaseTower
{
public:
	// Constructor & Deconstructor
	LightningTower(CP_Vector position);
	~LightningTower();
	// Attack is overridden to spawn LightningProjectile that chains to nearby enemies
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	void levelUp() override;
};

