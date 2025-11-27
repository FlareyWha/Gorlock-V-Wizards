/*!
@file       FireTower.h
@author     Bay Yeok Hao (yeokhao.bay)
@co-author
@brief		Contains declarations of functions, overrides and variables used by FireTower
*//*_______________________________________________________________________*/

#pragma once
#include "BaseTower.h"

class FireTower : public BaseTower
{
public:
	// Constructor & Deconstructor
	FireTower(CP_Vector position);
	~FireTower();
	// Attack is overriden to spawn FireProjectile that deals damage over time to enemy
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	void levelUp() override;
};
