#pragma once
#include "BaseProjectile.h"
#include "../../Particles/FireParticle.h"
#include "cprocessing.h"
#include <vector>

class FireProjectile : public BaseProjectile
{
public:
    FireProjectile();
    FireProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
    ~FireProjectile();

    void onHit(BaseEnemy* enemy) override;
    void Update() override;
    void Render() override;

private:
    std::vector<FireParticle*> particles;
    void SpawnParticles();
};