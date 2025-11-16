#pragma once
#include "BaseTower.h"

class FireTower : public BaseTower
{
public:
	FireTower(CP_Vector position);
	~FireTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	void levelUp() override;
};
