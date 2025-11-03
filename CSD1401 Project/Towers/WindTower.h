#pragma once
#include "BaseTower.h"
#include "../../Projectiles/BaseProjectile.h"
class WindTower : public virtual BaseTower
{
private:
	std::string towerName = "WindTower";
public:
	WindTower(CP_Vector position);
	~WindTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
};

