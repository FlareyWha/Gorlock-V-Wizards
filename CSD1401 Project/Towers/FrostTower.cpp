#include "FrostTower.h"
#include "../Projectiles/IceProjectile.h"
#include "../Projectiles/BaseProjectile.h"
#include "../System/SoundManager.h"

FrostTower::FrostTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 0, 255, 255));
	this->setDamage(2.0f);
	this->setSpeed(100.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/frostTower.png");
	setCooldown(1.0f);
	setTowerType(TOWER_TYPE::FROSTTOWER);
	this->setSaleAmt((int)(750 * 2 * 0.85));
	trackedEnemy = nullptr;
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
		CP_Vector unNormDirection = CP_Vector_Set(trackedEnemy->GetLocation().x - getPosition().x, trackedEnemy->GetLocation().y - getPosition().y);
		CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(trackedEnemy->GetLocation().x - getPosition().x, trackedEnemy->GetLocation().y - getPosition().y));
		//printf("%f %f\n", trackedEnemy->GetLocation().x, trackedEnemy->GetLocation().y);
		beamAngle = CP_Math_Degrees(atan2f(direction.y, direction.x));		

		beamLength = CP_Vector_Length(unNormDirection);

		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
		CP_Settings_RectMode(CP_POSITION_CORNER);
		if (beamLength <= getDetectionDistance() + 25.f)
			CP_Graphics_DrawRectAdvanced(this->getPosition().x, this->getPosition().y, beamLength, 10.f, beamAngle, 10.f);
		CP_Settings_RectMode(CP_POSITION_CENTER);

		if (trackedEnemy->GetHealth() <= 0.f)
		{
			trackedEnemy = nullptr;
		}
	}
}

BaseProjectile* FrostTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	
	setCooldownTime(getCooldown());

	return new IceProjectile(enemy->GetLocation(), direction, this->getDamage(), this->getSpeed(), this->getColor() , 3);
}

void FrostTower::TrackEnemy(std::vector<BaseEnemy*>& enemyList)
{
	bool withinRange = false;
	beamLength = 0.f;
	if (trackedEnemy != nullptr)
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
	else if (!withinRange)
	{
		for (BaseEnemy* enemy : enemyList)
		{
			if (CP_Vector_Distance(getPosition(), enemy->GetLocation()) <= 150.f)
			{
				trackedEnemy = enemy;
				SoundManager::GetInstance()->playSFX(TOWER_FREEZE_ATTACK_SFX);
				break;
			}

		}
	}
}