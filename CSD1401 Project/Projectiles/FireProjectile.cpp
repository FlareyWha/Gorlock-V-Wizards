#include "FireProjectile.h"

FireProjectile::FireProjectile()
{
}

FireProjectile::FireProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);

	setLifespan(5.0f);
}

FireProjectile::~FireProjectile()
{
}

void FireProjectile::onHit(BaseEnemy* enemy)
{
	if (enemy->IsBurned() == false)
	{
		enemy->Burn(true);
	}
}
