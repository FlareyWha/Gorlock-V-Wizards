#include "WindProjectile.h"
WindProjectile::WindProjectile()
{
	setProjDamage(1.f);
}

WindProjectile::WindProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);

	setLifespan(5.0f);
}

WindProjectile::~WindProjectile()
{
}

void WindProjectile::onHit(BaseEnemy* enemy)
{
	enemy->SetHealth(enemy->GetHealth() - getProjDamage());
}
