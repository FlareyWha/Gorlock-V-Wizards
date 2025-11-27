#include "LightningProjectile.h"
#include "../System/SoundManager.h"
#include <math.h>
#include "../Utils/Utils.h"
/*!
@file       LightningProjectile.cpp
@author     Chew Zavier (c.zavier)
@brief		Contains definitions of functions, overrides and variables used by Lightning Projectiles
*//*_______________________________________________________________________*/
//constructor
LightningProjectile::LightningProjectile(CP_Vector pos, CP_Vector dir, float damage, float speed, CP_Color color)
    : BaseProjectile(pos, dir, damage, speed, color)
{
    setProjType(PROJECTILE_TYPE::CHAIN);
    hasHit = false;
    lingerTime = 0.15f;
}
//overrided on hit 
void LightningProjectile::onHit(BaseEnemy* enemy)
{
    hasHit = true;
    setProjSpeed(0);
    lingerTime = 0.15f;

    enemy->SetHealth(enemy->GetHealth() - getProjDamage());//damage
    SoundManager::GetInstance()->playSFX(TOWER_LIGHTNING_ATTACK_SFX);

    SpawnLightningLine(GetLocation(), enemy->GetLocation());
}

void LightningProjectile::chainHit(std::vector<BaseEnemy*> enemyList, BaseEnemy* specificEnemy)
{
    for (BaseEnemy* enemy : enemyList)
    {
        if (counter >= maxChain) break;//if its alr max chained
        if (!areCirclesIntersecting(specificEnemy->GetLocation(), chainRadius,//else just check if theyre within range
            enemy->GetLocation(), enemy->GetSpriteSize() / 2.0f))
            continue;

        onHit(enemy);//hit them
        SpawnLightningLine(specificEnemy->GetLocation(), enemy->GetLocation());
        specificEnemy = enemy;
        counter++;
    }
}

void LightningProjectile::SpawnLightningLine(CP_Vector start, CP_Vector end)
{
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float len = sqrtf(dx * dx + dy * dy);
    float ang = atan2f(dy, dx);

    particles.emplace_back(start, len, ang, 5);
}

void LightningProjectile::Update()
{
    if (!hasHit)
        BaseProjectile::Update();

    for (int i = (int)particles.size() - 1; i >= 0; i--)
    {
        particles[i].Update();
        if (particles[i].life <= 0)
            particles.erase(particles.begin() + i);
    }

    if (hasHit)
    {
        lingerTime -= CP_System_GetDt();
        if (lingerTime <= 0.f && particles.empty())
            setLifespan(0.f);
    }
}

void LightningProjectile::Render()
{
    for (auto& p : particles)
        p.Draw();
}
