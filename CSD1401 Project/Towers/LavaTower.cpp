#include "LavaTower.h"
#include "../Projectiles/BaseProjectile.h"
#include "../Projectiles/FireProjectile.h"
#include "../Projectiles/LavaWall.h"
LavaTower::LavaTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/lavaTower.png");
	this->setColor(CP_Color_Create(255, 0, 0, 255));
	this->setDamage(1.0f);
	this->setSpeed(100.f);
	this->setSecondaryCD(1.0f);
	this->setMaxSecondaryCD(10.f);
	setCooldown(1.0f);
	setTowerType(TOWER_TYPE::LAVATOWER);
}

LavaTower::~LavaTower()
{
	CP_Image_Free(towerSprite);
}

BaseProjectile* LavaTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	SoundManager::GetInstance()->playSFX(TOWER_FIRE_ATTACK_SFX);
	return new FireProjectile(getPosition(), direction, this->getDamage(), this->getSpeed(), this->getColor());
}

BaseProjectile* LavaTower::SpawnSecondary(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setSecondaryCD(2.f);
	return new LavaWall(enemy->GetLocation(), enemy->GetDirectionVector(), this->getDamage(), 0, this->getColor());
}

