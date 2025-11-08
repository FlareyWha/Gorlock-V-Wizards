#include "IceTower.h"
#include "../Projectiles/IceProjectile.h"
#include "../../Projectiles/BaseProjectile.h"
IceTower::IceTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 0, 255, 255));
	this->setDamage(2.0f);
	this->setSpeed(100.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/iceTower.png");
	setCooldown(1.0f);
	setTowerType(TOWER_TYPE::ICETOWER);
}

IceTower::~IceTower()
{
	CP_Image_Free(towerSprite);
}

BaseProjectile* IceTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new IceProjectile(getPosition(), direction, this->getDamage(), this->getSpeed(), this->getColor());
}
