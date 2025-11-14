#include "HurricaneProjectile.h"

HurricaneProjectile::HurricaneProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);

	setLifespan(3.0f);
}

HurricaneProjectile::~HurricaneProjectile()
{
}


