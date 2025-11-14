#include "FrostTower.h"
#include "../Projectiles/IceProjectile.h"
#include "../Projectiles/BaseProjectile.h"

FrostTower::FrostTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 0, 255, 255));
	this->setDamage(2.0f);
	this->setSpeed(100.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/frostTower.png");
	setCooldown(1.0f);
	setTowerType(TOWER_TYPE::FROSTTOWER);
}

FrostTower::~FrostTower()
{
	CP_Image_Free(towerSprite);
}

void FrostTower::Update()
{
	cooldownTime -= 1.f * CP_System_GetDt();

	if (trackedEnemy)
	{
		//printf("%f %f\n", trackedEnemy->GetLocation().x, trackedEnemy->GetLocation().y);
		
		CP_Vector unNormDirection = CP_Vector_Set(trackedEnemy->GetLocation().x - getPosition().x, trackedEnemy->GetLocation().y - getPosition().y);
		CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(trackedEnemy->GetLocation().x - getPosition().x, trackedEnemy->GetLocation().y - getPosition().y));
		float angle = CP_Math_Degrees(atan2f(direction.y, direction.x));		

		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Graphics_DrawRectAdvanced(this->getPosition().x, this->getPosition().y, CP_Vector_Length(unNormDirection), 10.f, angle, 10.f);
		CP_Settings_RectMode(CP_POSITION_CENTER);
	}
}

BaseProjectile* FrostTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	
	setCooldownTime(getCooldown());

	return new IceProjectile(enemy->GetLocation(), direction, this->getDamage(), this->getSpeed(), this->getColor());
}

void FrostTower::TrackEnemy(std::vector<BaseEnemy*>& enemyList)
{
	bool withinRange = false;
	if (trackedEnemy)
	{
		for (BaseEnemy* enemy : enemyList)
		{
			if (CP_Vector_Distance(getPosition(), trackedEnemy->GetLocation()) <= 150.f)
			{
				withinRange = true;
				break;
			}
		}
	}

	if (!withinRange)
	{
		trackedEnemy = nullptr;

		for (BaseEnemy* enemy : enemyList)
		{
			if (CP_Vector_Distance(getPosition(), enemy->GetLocation()) <= 150.f)
			{
				trackedEnemy = enemy;
				break;
			}

		}
	}

}