#include "LightningProjectile.h"
#include "../System/SoundManager.h"
#include <math.h>
#include "../Utils/Utils.h"

LightningProjectile::LightningProjectile(CP_Vector pos, CP_Vector dir, float damage, float speed, CP_Color color)
    : BaseProjectile(pos, dir, damage, speed, color)
{
    setProjType(PROJECTILE_TYPE::CHAIN);
    hasHit = false;
    lingerTime = 0.15f;
}

void LightningProjectile::onHit(BaseEnemy* enemy)
{
    hasHit = true;
    setProjSpeed(0); // stop movement
    lingerTime = 0.15f;

    enemy->SetHealth(enemy->GetHealth() - getProjDamage());
    SoundManager::GetInstance()->playSFX(TOWER_LIGHTNING_ATTACK_SFX);

    // Spawn visual lightning directly on enemy
    SpawnLightningLine(GetLocation(), enemy->GetLocation());
}

void LightningProjectile::chainHit(std::vector<BaseEnemy*> enemyList, BaseEnemy* specificEnemy)
{
    for (BaseEnemy* enemy : enemyList)
    {
        if (counter >= maxChain) break;
        if (!areCirclesIntersecting(specificEnemy->GetLocation(), chainRadius,
            enemy->GetLocation(), enemy->GetSpriteSize() / 2.0f))
            continue;

        onHit(enemy); // damage + lightning
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

    particles.emplace_back(start, len, ang, 5); // short-lived streak
}

void LightningProjectile::Update()
{
    if (!hasHit)
        BaseProjectile::Update();

    // Update particles
    for (int i = (int)particles.size() - 1; i >= 0; i--)
    {
        particles[i].Update();
        if (particles[i].life <= 0)
            particles.erase(particles.begin() + i);
    }

    // Destroy projectile after linger time
    if (hasHit)
    {
        lingerTime -= CP_System_GetDt();
        if (lingerTime <= 0.f && particles.empty())
            setLifespan(0.f);
    }
}

void LightningProjectile::Render()
{
    // Optionally hide the projectile itself
    // BaseProjectile::Render();

    for (auto& p : particles)
        p.Draw();
}
