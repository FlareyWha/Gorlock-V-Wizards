#pragma once
#include "cprocessing.h"
#include "BaseProjectile.h"
class WindProjectile:public virtual BaseProjectile
{
private:
public:
	WindProjectile();
	WindProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~WindProjectile();
	void onHit(BaseEnemy* enemy) override;
};

