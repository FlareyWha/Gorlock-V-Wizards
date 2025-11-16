#include "FireTower.h"
#include "../Projectiles/BaseProjectile.h"
#include "../Projectiles/FireProjectile.h"
FireTower::FireTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/fireTower.png");
	this->setColor(CP_Color_Create(255, 0, 0, 255));
	this->setDamage(1.0f);
	this->setSpeed(500.f);
	setCooldown(1.0f);
	setTowerType(TOWER_TYPE::FIRETOWER);
	setLevel(1);
	setMaxLevel(3);
	setUpgradeCosts(50);
}

FireTower::~FireTower()
{
	CP_Image_Free(towerSprite);
}

BaseProjectile* FireTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	SoundManager::GetInstance()->playSFX(TOWER_FIRE_ATTACK_SFX);
	return new FireProjectile(getPosition(), direction, this->getDamage(), this->getSpeed(), this->getColor());
}

void FireTower::levelUp()
{
	BaseTower::levelUp();
	this->setDamage(1.0f * this->getLevel());
}
