#include "WindTower.h"
#include "../../Projectiles/BaseProjectile.h"
#include <stdio.h>
WindTower::WindTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 255, 0, 255));
	this->setDamage(0.5f);
	this->setSpeed(500.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/windTower.png");
	setCooldown(0.25f);
}

WindTower::~WindTower()
{
	CP_Image_Free(towerSprite);
}

BaseProjectile* WindTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new BaseProjectile(getPosition(), direction, this->getDamage(),2000.f,this->getColor());
}