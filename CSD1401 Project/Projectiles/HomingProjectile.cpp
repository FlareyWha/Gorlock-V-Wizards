#include "HomingProjectile.h"

void HomingProjectile::setHomingSpeed(float speed)
{
	this->homingSpeed = speed;
}

float HomingProjectile::getHomingSpeed()
{
	return this->homingSpeed;
}

HomingProjectile::HomingProjectile(BaseEnemy* enemy, CP_Vector initialPos, CP_Vector initialDirection, float damage, float speed, CP_Color color)
{
	this->setDirection(initialDirection);
	this->trackingEnemy = enemy;
	this->setPosition(initialPos);
	this->setProjDamage(damage);
	this->setProjSpeed(speed/2.f);
	setHomingSpeed(speed);
	this->setProjColor(CP_Color_Create(255,0,255,255));
	timer = initialTimer;

	setLifespan(10.f);
}

void HomingProjectile::Update()
{
	BaseProjectile::Update();
	timer += -1 * CP_System_GetDt();
	if (timer <= 0)
	{
		setProjSpeed(getHomingSpeed());
		CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(trackingEnemy->GetLocation().x - GetLocation().x, trackingEnemy->GetLocation().y - GetLocation().y));
		setDirection(direction);
	}
}
