#pragma once
#include "BaseTower.h"
#include "cprocessing.h"
class HurricaneTower : public BaseTower
{
private: 

public:
	HurricaneTower(CP_Vector position);
	~HurricaneTower();

	BaseProjectile* Attack(BaseEnemy* enemy) override;
	BaseProjectile* SpawnSecondary(std::vector<BaseEnemy*>* enemyList,BaseEnemy* specificEnemy) override;
};

