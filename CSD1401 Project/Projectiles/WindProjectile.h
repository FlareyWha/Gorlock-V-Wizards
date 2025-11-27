#pragma once
#include "BaseProjectile.h"
#include "../Particles/WindParticle.h"
#include "cprocessing.h"
#include <vector>
/*!
@file       WindProjectile.h
@author     Chew Zavier (c.zavier)
@brief		Contains declarations of functions, overrides and variables used by Wind Projectiles
*//*_______________________________________________________________________*/
class WindProjectile : public BaseProjectile
{
private:
    std::vector<WindParticle*> particles;
    void SpawnParticles();

public:
    //default constructor
    WindProjectile();
    //constructor for easier spawning
    WindProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
    //destructor
    ~WindProjectile();

    void onHit(BaseEnemy* enemy) override;//overrided onhit
    void Update() override;
    void Render() override;

};

