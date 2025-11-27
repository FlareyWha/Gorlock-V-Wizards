#include "WindProjectile.h"
#include <cstdlib> // for rand()

WindProjectile::WindProjectile() {}
//constructor
WindProjectile::WindProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
    : BaseProjectile(position, direction, damage, speed, color)
{
}
//destructor
WindProjectile::~WindProjectile()
{
    for (auto p : particles)
        delete p;
    particles.clear();
}
//overrided onhits
void WindProjectile::onHit(BaseEnemy* enemy)
{
    enemy->SetHealth(enemy->GetHealth() - getProjDamage());
}

void WindProjectile::SpawnParticles()
{
    for (int i = 0; i < 2; ++i)
    {
        CP_Vector vel = CP_Vector_Set(
            ((rand() % 20) - 10) * 0.05f,
            ((rand() % 20) - 10) * 0.05f
        );
        particles.push_back(new WindParticle(GetLocation(), vel, 30));
    }
}

void WindProjectile::Update()
{
    BaseProjectile::Update();
    SpawnParticles();

    for (auto it = particles.begin(); it != particles.end(); )
    {
        WindParticle* p = *it;
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

void WindProjectile::Render()
{
    BaseProjectile::Render();

    for (auto& p : particles)
        p->Draw();
}