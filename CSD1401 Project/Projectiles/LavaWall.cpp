#include "LavaWall.h"

#include "../System/SoundManager.h"

LavaWall::LavaWall(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	setPosition(position);
	setDirection(direction);
	setProjDamage(damage);
	setProjSpeed(speed);
	setProjColor(color);
	setLifespan(10.f);

	setProjType(PROJECTILE_TYPE::DAMAGEOVERTIME);
}

LavaWall::~LavaWall()
{
}

void LavaWall::Update()
{
	BaseProjectile::Update();
	hitCD += -1 * CP_System_GetDt();

	sfxTimer -= CP_System_GetDt();
	sfxTimer = CP_Math_ClampFloat(sfxTimer, 0.f, 1.f);
}

void LavaWall::Render()
{
	CP_Settings_Fill(getProjColor());
	float angle = CP_Math_Degrees(atan2f(this->getDirection().y, this->getDirection().x));
	//angle = (angle < 90 && angle > 0) ? 0 : angle > 90 ? 0 : 90;
	//printf("Angle: %f\n", angle);
	CP_Graphics_DrawRectAdvanced(this->GetLocation().x, this->GetLocation().y, 15.f,50.f,angle,10.f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
}

void LavaWall::onHit(BaseEnemy* enemy)
{
	
	enemy->SetHealth(enemy->GetHealth() - 0.5);
	//if (!enemy->IsBurned())
	//	enemy->Burn(true);
	hitCD = hitMaxCD;

	if (sfxTimer <= 0.f)
	{
		SoundManager::GetInstance()->playSFX(TOWER_LAVA_ATTACK_SFX);
		sfxTimer = sfxMaxTimer;
	}
}



