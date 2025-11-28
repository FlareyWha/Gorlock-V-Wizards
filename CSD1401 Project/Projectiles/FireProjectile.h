/*!
@file       FireProjectile.h
@author     Chew Zavier (c.zavier)
@brief		Contains declarations of functions, overrides and variables used by FireProjectile
*//*_______________________________________________________________________*/

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
    //constructor
    FireProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
    //destructor
    ~FireProjectile();
    //onhit override so as to achieve different effects
    void onHit(BaseEnemy* enemy) override;
    void Update() override;
    void Render() override;

};