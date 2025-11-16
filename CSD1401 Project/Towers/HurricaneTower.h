#pragma once
#include "BaseTower.h"
#include "cprocessing.h"
class HurricaneTower : public virtual BaseTower
{
private: 

public:
	HurricaneTower(CP_Vector position);
	~HurricaneTower();

	BaseProjectile* Attack(BaseEnemy* enemy) override;
	BaseProjectile* SpawnSecondary(BaseEnemy* enemy) override;
};

