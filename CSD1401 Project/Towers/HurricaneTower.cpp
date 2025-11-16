#include "HurricaneTower.h"
#include "../Projectiles/BaseProjectile.h"
#include "../Projectiles/HurricaneProjectile.h"
#include "../Projectiles/HomingProjectile.h"
HurricaneTower::HurricaneTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 0, 255, 255));
	this->setDamage(1.f);
	this->setSpeed(500.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/hurricaneTower.png");
	setCooldown(0.1f);
	setTowerType(TOWER_TYPE::HURRICANETOWER);
	this->setMaxSecondaryCD(getCooldown() * 3.f);
}

HurricaneTower::~HurricaneTower()
{
}


BaseProjectile* HurricaneTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new HurricaneProjectile(this->getPosition(),direction,this->getDamage(),this->getSpeed(),this->getColor());
}

BaseProjectile* HurricaneTower::SpawnSecondary(BaseEnemy* enemy)
{
	CP_Vector initialDirection = CP_Vector_Negate( CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y)));
	this->setSecondaryCD(this->getMaxSecondaryCD());
	return new HomingProjectile(enemy,this->getPosition(),initialDirection,this->getDamage(),this->getSpeed(),this->getColor());
}


