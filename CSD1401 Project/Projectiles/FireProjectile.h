#pragma once
#include "BaseProjectile.h"
#include "../Particles/FireParticle.h"
#include "cprocessing.h"
#include <vector>

class FireProjectile : public BaseProjectile
{
private:
    std::vector<FireParticle*> particles;
    void SpawnParticles();
public:
    FireProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
    ~FireProjectile();

    void onHit(BaseEnemy* enemy) override;
    void Update() override;
    void Render() override;

};