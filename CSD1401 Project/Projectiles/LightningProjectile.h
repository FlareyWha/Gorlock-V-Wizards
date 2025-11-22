#pragma once
#include "../Particles/LightningParticle.h"
#include "BaseProjectile.h"
#include <vector>

class LightningProjectile : public BaseProjectile
{
protected:
    std::vector<LightningParticle> particles;
    bool hasHit = false;
    float lingerTime = 0.1f;
    int counter = 0;
    const int maxChain = 3;
    float chainRadius = 100.f;

public:
    LightningProjectile(CP_Vector pos, CP_Vector dir, float damage, float speed, CP_Color color);

    void Update() override;
    void Render() override;
    void onHit(BaseEnemy* enemy) override;
    void chainHit(std::vector<BaseEnemy*> enemyList, BaseEnemy* specificEnemy);
    void SpawnLightningLine(CP_Vector start, CP_Vector end);
   
};


