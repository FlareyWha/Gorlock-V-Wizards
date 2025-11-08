#pragma once
#include "./BaseProjectile.h"
class FireProjectile:public virtual BaseProjectile
{
public:
	FireProjectile();
	FireProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~FireProjectile();
	void onHit(BaseEnemy* enemy) override;
};

