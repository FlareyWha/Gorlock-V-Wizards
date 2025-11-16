#include "FireProjectile.h"
#include "../Particles/FireParticle.h"
#include <cstdlib>

FireProjectile::FireProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
    : BaseProjectile(position, direction, damage, speed, color)
{
    FireParticle::LoadImage("Assets/Particles/Fire.png");
    this->setProjColor(color);
    this->setProjSpeed(speed);
    this->setProjDamage(damage);

}

FireProjectile::~FireProjectile()
{
    for (auto p : particles)
        delete p;
    particles.clear();
}

void FireProjectile::onHit(BaseEnemy* enemy)
{
    enemy->SetHealth(enemy->GetHealth() - this->getProjDamage());
    if (!enemy->IsBurned())
        enemy->Burn(true);
}

void FireProjectile::SpawnParticles()
{
    for (int i = 0; i < 1; ++i)
    {
        CP_Vector vel = CP_Vector_Set(
            ((rand() % 20) - 10) * 0.05f,
            ((rand() % 20) - 10) * 0.05f
        );

        particles.push_back(new FireParticle(GetLocation(), vel, 10));
    }
}

void FireProjectile::Update()
{
    BaseProjectile::Update();

    SpawnParticles();

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
    BaseProjectile::Render();

    for (auto& p : particles)
        p->Draw();
}
