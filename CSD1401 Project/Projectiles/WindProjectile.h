#pragma once
#include "BaseProjectile.h"
#include "../../Particles/WindParticle.h"
#include "cprocessing.h"
#include <vector>

class WindProjectile : public virtual BaseProjectile
{
public:
    WindProjectile();
    WindProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
    ~WindProjectile();

    void onHit(BaseEnemy* enemy) override;
    void Update() override;
    void Render() override;

private:
    std::vector<WindParticle*> particles;
    void SpawnParticles();
};

