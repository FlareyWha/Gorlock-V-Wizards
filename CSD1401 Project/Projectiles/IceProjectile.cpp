#include "IceProjectile.h"

IceProjectile::IceProjectile()
{
}

IceProjectile::IceProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color,int level)
{
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);
	this->level = level;
	setLifespan(5.0f);
}

IceProjectile::~IceProjectile()
{
}

void IceProjectile::onHit(BaseEnemy* enemy)
{
	enemy->SetHealth(enemy->GetHealth() - this->getProjDamage());
	if (enemy->IsSlowed() == false)
	{ 
		switch (this->level)
		{
		case 1:
			slowFactor = 0.75f;
			break;
		case 2:
			slowFactor = 0.5f;
			break;
		case 3:
			slowFactor = 0.25f;
			break;
		}
		enemy->Slow(true,slowFactor);
	}
}
