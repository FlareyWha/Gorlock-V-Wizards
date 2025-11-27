#include "WindTower.h"
#include "../Projectiles/WindProjectile.h"
#include "../Projectiles/BaseProjectile.h"
#include <stdio.h>
/*!
@file		WindTower.cpp
@author     Chew Zavier (c.zavier)
@brief		Contains definitions of functions, overrides and variables used by Wind Tower
*//*_______________________________________________________________________*/
//constructor
WindTower::WindTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 255, 0, 255));
	this->setDamage(0.25f);
	this->setSpeed(500.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/windTower.png");
	setCooldown(0.25f);
	setTowerType(TOWER_TYPE::WINDTOWER);
	setUpgradeCosts(200);
	this->setBaseSaleAmt(150);
	this->setSaleAmt((int)(this->getBaseSaleAmt() * 0.85));
}

//destructor
WindTower::~WindTower()
{
	CP_Image_Free(towerSprite);
}
//overrided attack to spawn windprojectile
BaseProjectile* WindTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	SoundManager::GetInstance()->playSFX(TOWER_WIND_ATTACK_SFX);
	return new WindProjectile(getPosition(), direction, this->getDamage(),this->getSpeed(), this->getColor());
}
//overrided levelup to change damage and further increase attackspeed
void WindTower::levelUp()
{
	BaseTower::levelUp();
	this->setDamage(0.25f * level);
	switch (level) {
	case 2:
		setCooldown(0.20f);
		break;
	case 3:
		setCooldown(0.1f);
		break;
	default:
		setCooldown(0.25f);
		break;
	}
}
