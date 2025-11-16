#include "IceTower.h"
#include "../Projectiles/IceProjectile.h"
#include "../Projectiles/BaseProjectile.h"

#include <math.h>
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
	
	//CP_Vector unNormDirection = CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y);
	//float angle = CP_Math_Degrees(atan2f(direction.y, direction.x));
	//printf("%f\n", angle);
	//CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	//CP_Settings_RectMode(CP_POSITION_CORNER);
	//CP_Graphics_DrawRectAdvanced(this->getPosition().x, this->getPosition().y, CP_Vector_Length(unNormDirection), 10.f, angle, 10.f);
	//CP_Settings_RectMode(CP_POSITION_CENTER);
	
	setCooldownTime(getCooldown());
	return new IceProjectile(getPosition(), direction, this->getDamage(), this->getSpeed(), this->getColor(),this->getLevel());
}

void IceTower::levelUp()
{
	BaseTower::levelUp();
	this->setDamage(1.0f * ((float)this->getLevel()* 0.65f));
}
