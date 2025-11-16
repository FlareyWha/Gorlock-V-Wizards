#pragma once
#include "BaseTower.h"
class LavaTower : public BaseTower
{
public:
	LavaTower(CP_Vector position);
	~LavaTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	BaseProjectile* SpawnSecondary(BaseEnemy* enemy) override;
};

