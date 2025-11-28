/*!
@file       IceTower.cpp
@author     Chew Zavier (c.zavier)
@brief		Contains definitions of functions, overrides and variables used by IceTower
*//*_______________________________________________________________________*/

#include <math.h>
#include "IceTower.h"
#include "../Projectiles/IceProjectile.h"
#include "../Projectiles/BaseProjectile.h"
#include "../System/SoundManager.h"

// Constructor & Destructor
IceTower::IceTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 0, 255, 255));
	this->setDamage(2.0f);
	this->setSpeed(100.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/iceTower.png");
	setCooldown(1.0f);
	setTowerType(TOWER_TYPE::ICETOWER);
	setUpgradeCosts(125);
	this->setBaseSaleAmt(125);
	this->setSaleAmt((int)(this->getBaseSaleAmt() * 0.85));
}

IceTower::~IceTower()
{
	CP_Image_Free(towerSprite);
}

// Attack is overridden to spawn IceProjectile
BaseProjectile* IceTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	
	SoundManager::GetInstance()->playSFX(TOWER_ICE_ATTACK_SFX);
	setCooldownTime(getCooldown());
	return new IceProjectile(getPosition(), direction, this->getDamage(), this->getSpeed(), this->getColor(),this->getLevel());
}

void IceTower::levelUp()
{
	BaseTower::levelUp();
	this->setDamage(1.0f * ((float)this->getLevel()* 0.65f));
}
