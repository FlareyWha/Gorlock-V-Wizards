#include "LightningTower.h"
#include "../Projectiles/LightningProjectile.h"
LightningTower::LightningTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(255, 255, 0, 255));
	this->setDamage(10.f);
	this->setSpeed(750.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/lightningTower.png");
	setCooldown(2.f);
	setTowerType(TOWER_TYPE::LIGHTNINGTOWER);
}

LightningTower::~LightningTower()
{
	CP_Image_Free(towerSprite);
}

BaseProjectile* LightningTower::Attack(BaseEnemy* enemy)
{

	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new LightningProjectile(getPosition(), direction, this->getDamage(), this->getSpeed(), this->getColor());
}
