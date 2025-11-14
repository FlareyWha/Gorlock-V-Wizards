#pragma once
#include "BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"
class LightningProjectile:public virtual BaseProjectile
{
private:
	int maxChain = 3;
	int counter = 0;
	float chainRadius = 50.f;

public:
	float chainLifespan = 2.f;
	LightningProjectile();
	LightningProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~LightningProjectile();

	void onHit(BaseEnemy* enemy) override;
	void chainHit(std::vector<BaseEnemy*> enemyList, BaseEnemy* specificEnemy) override;

};

