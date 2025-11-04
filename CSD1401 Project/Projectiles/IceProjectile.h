#pragma once
#include "BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"
class IceProjectile:public virtual BaseProjectile
{
public:
	IceProjectile();
	IceProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~IceProjectile();
	void onHit(BaseEnemy* enemy) override;
};

