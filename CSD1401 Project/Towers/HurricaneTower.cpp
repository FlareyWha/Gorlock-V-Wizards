/*!
@file       HurricaneTower.cpp
@author     Chew Zavier (c.zavier)
@brief		Contains definitions of functions, overrides and variables used by HurricaneTower
*//*_______________________________________________________________________*/

#include "HurricaneTower.h"
#include "../Projectiles/BaseProjectile.h"
#include "../Projectiles/HurricaneProjectile.h"
#include "../Projectiles/HomingProjectile.h"

//Constructor
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
	this->setSaleAmt((int)(750 * 2 * 0.85));
}
//destructor
HurricaneTower::~HurricaneTower()
{
}


BaseProjectile* HurricaneTower::Attack(BaseEnemy* enemy)//override attack to spawn hurricane projectiles intead
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new HurricaneProjectile(this->getPosition(),direction,this->getDamage(),this->getSpeed(),this->getColor());
}

BaseProjectile* HurricaneTower::SpawnSecondary(std::vector<BaseEnemy*>* enemyList,BaseEnemy* specificEnemy)//override to spawn the homing missiles instead
{
	CP_Vector initialDirection = CP_Vector_Negate( CP_Vector_Normalize(CP_Vector_Set(specificEnemy->GetLocation().x - getPosition().x, specificEnemy->GetLocation().y - getPosition().y)));
	this->setSecondaryCD(this->getMaxSecondaryCD());
	return new HomingProjectile(specificEnemy,enemyList, this->getPosition(), initialDirection, this->getDamage(), this->getSpeed(), this->getColor());
}


