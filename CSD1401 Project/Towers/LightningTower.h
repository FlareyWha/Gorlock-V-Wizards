#pragma once
#include "BaseTower.h"
class LightningTower : public virtual BaseTower
{
public:
	LightningTower(CP_Vector position);
	~LightningTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	void levelUp() override;
};

