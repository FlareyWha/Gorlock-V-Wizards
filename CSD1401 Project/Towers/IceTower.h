#pragma once
#include "BaseTower.h"
#include "../Projectiles/BaseProjectile.h"
class IceTower:public virtual BaseTower
{
private:
	std::string towerName = "WindTower";
public:
	IceTower(CP_Vector position);
	~IceTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
};

