/*!
@file       LightningProjectile.h
@author     Chew Zavier (c.zavier)
@brief		Contains declaration of functions, overrides and variables used by LightningProjectile
*//*_______________________________________________________________________*/

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
    int counter = 0;//counter for how many it has chained to
    const int maxChain = 3;//maximum number of chains
    float chainRadius = 100.f;//radius for chaining

public:
    //constructor
    LightningProjectile(CP_Vector pos, CP_Vector dir, float damage, float speed, CP_Color color);

    void Update() override;
    void Render() override;
    void onHit(BaseEnemy* enemy) override;//overrided for chaining
    void chainHit(std::vector<BaseEnemy*> enemyList, BaseEnemy* specificEnemy);//chains the hits between enemies
    void SpawnLightningLine(CP_Vector start, CP_Vector end);
   
};


