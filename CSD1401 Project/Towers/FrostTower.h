#pragma once
#include "BaseTower.h"
#include "../../Projectiles/BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"

class FrostTower : public BaseTower
{
public:
	FrostTower(CP_Vector position);
	~FrostTower();

	void Update() override;

	BaseProjectile* Attack(BaseEnemy* enemy) override;

	void TrackEnemy(std::vector<BaseEnemy*>& enemyList);
	BaseEnemy* trackedEnemy;
};
