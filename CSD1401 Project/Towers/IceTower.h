/*!
@file       IceTower.h
@author     Chew Zavier(c.zavier)
@co-author
@brief		Contains declarations of functions, overrides and variables used by IceTower
*//*_______________________________________________________________________*/

#pragma once
#include "BaseTower.h"
#include "../Projectiles/BaseProjectile.h"
class IceTower: public BaseTower
{
public:
	// Constructor & Destructor
	IceTower(CP_Vector position);
	~IceTower();
	// Attack is overridden to spawn IceProjectile that slows enemies
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	void levelUp() override;
};

