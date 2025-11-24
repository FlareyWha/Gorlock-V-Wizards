#include "StormTower.h"
#include "../Projectiles/LightningProjectile.h"
#include "../System/SoundManager.h"

StormTower::StormTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(255, 255, 0, 255));
	this->setDamage(5.f);
	this->setSpeed(750.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/stormTower.png");
	setCooldown(2.f);
	setTowerType(TOWER_TYPE::STORMTOWER);
	setSaleAmt((int)(575 * 2 * 0.85));
}

StormTower::~StormTower()
{
	CP_Image_Free(towerSprite);
}

void StormTower::Update()
{
	cooldownTime -= 1.f * CP_System_GetDt();

	if (cooldownTime >= 0 && enemyNearby)
	{
		CP_Settings_Fill(CP_Color_Create(255, 100, 255, (int)(255 * (cooldownTime / cooldown) * 0.75)));
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Graphics_DrawRectAdvanced(position.x, position.y, chainLength, 10.f, chainAngle, 10.f);
		CP_Settings_RectMode(CP_POSITION_CENTER);
	}
}


BaseProjectile* StormTower::Attack(BaseEnemy* enemy)
{
	if (CP_Vector_Distance(enemy->GetLocation(), getPosition()) <= getDetectionDistance())
	{
		enemyNearby = true;
		enemy->SetHealth(enemy->GetHealth() - getDamage());

		chainAngle = atan2f(enemy->GetLocation().y - position.y, enemy->GetLocation().x - position.x);
		chainAngle = CP_Math_Degrees(chainAngle);
		chainLength = CP_Vector_Distance(position, enemy->GetLocation());

		SoundManager::GetInstance()->playSFX(TOWER_LIGHTNING_ATTACK_SFX);
	}
	else
	{
		enemyNearby = false;
	}
	printf("%f\n", enemy->GetHealth());

	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new LightningProjectile(getPosition(), direction, this->getDamage(), this->getSpeed(), this->getColor());
}