#include "LightningProjectile.h"
#include "../Utils/Utils.h"
#include "../../System/SoundManager.h"
#include <stdio.h>
#include <math.h>

LightningProjectile::LightningProjectile()
{
}

LightningProjectile::LightningProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);
	setProjType(PROJECTILE_TYPE::CHAIN);

	setLifespan(5.0f);
}

LightningProjectile::~LightningProjectile()
{

}

void LightningProjectile::onHit(BaseEnemy* enemy)
{
	enemy->SetHealth(enemy->GetHealth() - getProjDamage());
	SoundManager::GetInstance()->playSFX(TOWER_LIGHTNING_ATTACK_SFX);
}

void LightningProjectile::chainHit(std::vector<BaseEnemy*> enemyList,BaseEnemy* specificEnemy)
{
	for (int i = 0; i< enemyList.size();i++)
	{
		if (counter < maxChain)
		{

			if (!areCirclesIntersecting(specificEnemy->GetLocation(), chainRadius, enemyList[i]->GetLocation(), enemyList[i]->GetSpriteSize() / 2.0f))
			{
				continue;
			}
			else if (areCirclesIntersecting(specificEnemy->GetLocation(), chainRadius, enemyList[i]->GetLocation(), enemyList[i]->GetSpriteSize() / 2.0f))
			{
				onHit(enemyList[i]);
				specificEnemy = enemyList[i];
				counter++;

				float angle = atan2f(specificEnemy->GetLocation().y - GetLocation().y, specificEnemy->GetLocation().x - GetLocation().x);
				angle = CP_Math_Degrees(angle);
				printf("%f\n", angle);

				CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
				CP_Settings_RectMode(CP_POSITION_CORNER);
				CP_Graphics_DrawRectAdvanced(GetLocation().x, GetLocation().y, CP_Vector_Distance(GetLocation(), specificEnemy->GetLocation()), 10.f, angle, 10.f);
				CP_Settings_RectMode(CP_POSITION_CENTER);
				
			}
		}
		if (counter >= maxChain)
		{
			break;
		}
	}
}


