#pragma once
#include "BaseTower.h"

class StormTower : public BaseTower
{
public:
	StormTower(CP_Vector position);
	~StormTower();

	void Update() override;
	BaseProjectile* Attack(BaseEnemy* enemy) override;

	float chainLength = 0.f, chainAngle = 0.f;
	bool enemyNearby = false;
};
