#include "FireProjectile.h"

FireProjectile::FireProjectile() {}

FireProjectile::FireProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
    : BaseProjectile(position, direction, damage, speed, color)
{
}

FireProjectile::~FireProjectile()
{
    // Free any remaining particles
    for (auto p : particles)
        delete p;
    particles.clear();
}

void FireProjectile::onHit(BaseEnemy* enemy)
{
    if (!enemy->IsBurned())
        enemy->Burn(true);
}

void FireProjectile::SpawnParticles()
{
    // spawn a few small particles at the projectile's position
    for (int i = 0; i < 2; ++i)
    {
        CP_Vector vel = CP_Vector_Set(
            ((rand() % 20) - 10) * 0.05f, // small horizontal drift
            ((rand() % 20) - 10) * 0.05f  // small vertical drift
        );

        particles.push_back(new FireParticle(GetLocation(), vel, 30)); // 30 frames lifetime
    }
}

void FireProjectile::Update()
{
    // Move projectile
    BaseProjectile::Update();

    // Spawn trail particles
    SpawnParticles();

    // Update particles
    for (auto it = particles.begin(); it != particles.end(); )
    {
        FireParticle* p = *it;
        p->Update();
        if (!p->IsAlive())
        {
            delete p;
            it = particles.erase(it);
        }
        else
            ++it;
    }
}

void FireProjectile::Render()
{
    // Draw projectile itself
    BaseProjectile::Render();

    // Draw particles
    for (auto& p : particles)
        p->Draw();
}
