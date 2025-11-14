#pragma once
#include "BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"
class IceProjectile:public virtual BaseProjectile
{
private:
	float slowFactor;
	int level;
public:
	IceProjectile();
	IceProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color , int level = 1);
	~IceProjectile();
	void onHit(BaseEnemy* enemy) override;
};

