#pragma once
#include "BaseTower.h"
#include "../Projectiles/BaseProjectile.h"
class WindTower : public virtual BaseTower
{
private:
	float baseDamage = 0.25f;
public:
	WindTower(CP_Vector position);
	~WindTower();
	BaseProjectile* Attack(BaseEnemy* enemy) override;
	void levelUp() override;
};

