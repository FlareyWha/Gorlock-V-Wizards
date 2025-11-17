#pragma once
#include "BaseTower.h"
#include "../Projectiles/BaseProjectile.h"
class IceTower: public BaseTower
{
public:
	IceTower(CP_Vector position);
	~IceTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	void levelUp() override;
};

