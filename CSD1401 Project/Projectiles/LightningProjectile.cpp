#include "LightningProjectile.h"
#include "../Utils/Utils.h"
#include "../../System/SoundManager.h"
#include <stdio.h>
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
	printf("chained: %d\n", counter);
	enemy->SetHealth(enemy->GetHealth() - getProjDamage());
	SoundManager::GetInstance()->playSFX(TOWER_LIGHTNING_ATTACK_SFX);
}

void LightningProjectile::chainHit(std::vector<BaseEnemy*> enemyList,BaseEnemy* specificEnemy)
{
	for (int i = 0; i< enemyList.size();i++)
	{
		if (counter < maxChain)
		{
			if (!areCirclesIntersecting(specificEnemy->GetLocation(), specificEnemy->GetSpriteSize() / 2.0f, enemyList[i]->GetLocation(), enemyList[i]->GetSpriteSize() / 2.0f))
			{
				continue;
			}
			else if (areCirclesIntersecting(specificEnemy->GetLocation(), specificEnemy->GetSpriteSize() / 2.0f, enemyList[i]->GetLocation(), enemyList[i]->GetSpriteSize() / 2.0f))
			{
				onHit(enemyList[i]);
				specificEnemy = enemyList[i];
				counter++;
			}
		}
		if (counter >= maxChain)
		{
			break;
		}
	}
}


