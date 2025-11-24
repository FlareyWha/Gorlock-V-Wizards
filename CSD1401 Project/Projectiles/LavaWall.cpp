#include "LavaWall.h"
#include "../System/SoundManager.h"

LavaWall::LavaWall(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
    FireParticle::LoadImage("Assets/Particles/Fire.png");

    setPosition(position);
    setDirection(direction);
    setProjDamage(damage);
    setProjSpeed(speed);
    setProjColor(color);
    setLifespan(10.f);

    setProjType(PROJECTILE_TYPE::DAMAGEOVERTIME);

    sfxTimer = 0.f;
    sfxMaxTimer = 0.5f;
}

LavaWall::~LavaWall()
{
    for (auto p : particles)
        delete p;
    particles.clear();
}

void LavaWall::Update()
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

    hitCD -= CP_System_GetDt();
    sfxTimer -= CP_System_GetDt();
    sfxTimer = CP_Math_ClampFloat(sfxTimer, 0.f, sfxMaxTimer);
}

void LavaWall::Render()
{
    CP_Settings_Fill(getProjColor());
    float angle = CP_Math_Degrees(atan2f(this->getDirection().y, this->getDirection().x));
    CP_Graphics_DrawRectAdvanced(this->GetLocation().x, this->GetLocation().y, 15.f, 50.f, angle, 10.f);

    for (auto& p : particles)
    {
        p->Draw();
    }

    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
}

void LavaWall::onHit(BaseEnemy* enemy)
{
    enemy->Burn(true);
    hitCD = hitMaxCD;

    if (sfxTimer <= 0.f)
    {
        SoundManager::GetInstance()->playSFX(TOWER_LAVA_ATTACK_SFX);
        sfxTimer = sfxMaxTimer;
    }
}

void LavaWall::SpawnParticles()
{
    for (int i = 0; i < 5; ++i)
    {
        CP_Vector vel = CP_Vector_Set(
            ((rand() % 20) - 10) * 0.05f,
            ((rand() % 20) - 10) * 0.05f
        );

        FireParticle* p = new FireParticle(GetLocation(), vel, 20);
        particles.push_back(p);
    }
}




