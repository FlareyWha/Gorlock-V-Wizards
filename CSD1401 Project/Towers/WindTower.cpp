#include "WindTower.h"
#include "../Projectiles/WindProjectile.h"
#include "../Projectiles/BaseProjectile.h"
#include <stdio.h>
WindTower::WindTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 255, 0, 255));
	this->setDamage(0.25f);
	this->setSpeed(500.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/windTower.png");
	setCooldown(0.25f);
	setTowerType(TOWER_TYPE::WINDTOWER);
	setUpgradeCosts(200.f);
}

WindTower::~WindTower()
{
	CP_Image_Free(towerSprite);
}

BaseProjectile* WindTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	SoundManager::GetInstance()->playSFX(TOWER_WIND_ATTACK_SFX);
	return new WindProjectile(getPosition(), direction, this->getDamage(),this->getSpeed(), this->getColor());
}

void WindTower::levelUp()
{
	if (level != maxLevel)
	{
		this->level++;
		this->setUpgradeCosts(levelUpCosts * level);
		CP_Math_ClampInt(level, 1, maxLevel);
	}
}
