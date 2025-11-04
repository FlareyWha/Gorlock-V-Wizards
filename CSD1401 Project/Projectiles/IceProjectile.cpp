#include "IceProjectile.h"

IceProjectile::IceProjectile()
{
}

IceProjectile::IceProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);

	setLifespan(5.0f);
}

IceProjectile::~IceProjectile()
{
}

void IceProjectile::onHit(BaseEnemy* enemy)
{
	if (enemy->IsSlowed() == false)
	{ 
		enemy->Slow(true);
	}
}
