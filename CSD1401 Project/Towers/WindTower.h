/*!
@file		WindTower.h
@author     Chew Zavier (c.zavier)
@brief		Contains declarations of functions, overrides and variables used by WindTower
*//*_______________________________________________________________________*/

#pragma once
#include "BaseTower.h"
#include "../Projectiles/BaseProjectile.h"

class WindTower : public BaseTower
{
private:
	float baseDamage = 0.25f;
public:
	//constructor
	WindTower(CP_Vector position);
	//destructor
	~WindTower();
	//overrided attack function to spawn wind projectile
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	//override levelup to change different attributes
	void levelUp() override;
};

