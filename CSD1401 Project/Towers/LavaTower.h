/*!
@file       LavaTower.h
@author     Chew Zavier(c.zavier)
@brief		Contains declarations of functions, overrides and variables used by Lava Tower
*//*_______________________________________________________________________*/
#pragma once
#include "BaseTower.h"
class LavaTower : public BaseTower
{
public:
	//constructor
	LavaTower(CP_Vector position);
	//destructor
	~LavaTower();
	//overrided attack function to spawn lava projectile
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	//overrided spawn secondary to spawn lava wall
	BaseProjectile* SpawnSecondary(BaseEnemy* enemy) override;
};

