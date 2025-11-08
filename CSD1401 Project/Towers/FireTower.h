#pragma once
#include "BaseTower.h"

class FireTower : public BaseTower
{
private:
	std::string towerName = "FireTower";
public:
	FireTower(CP_Vector position);
	~FireTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
};

