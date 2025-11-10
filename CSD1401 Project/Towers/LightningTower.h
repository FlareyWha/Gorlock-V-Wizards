#pragma once
#include "BaseTower.h"
class LightningTower : public virtual BaseTower
{
private:
	std::string towerName = "LightningTower";
public:
	LightningTower(CP_Vector position);
	~LightningTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
};

