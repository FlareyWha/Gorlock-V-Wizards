/*!
@file       IceProjectile.h
@author     Chew Zavier (c.zavier)
@brief		Contains declarations of functions, overrides and variables used by IceProjectiles
*//*_______________________________________________________________________*/

#pragma once
#include "BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"
#include "IceProjectile.h"
#include "../Particles/SnowParticle.h"
#include <cstdlib>

class IceProjectile: public BaseProjectile
{
private:
	float slowFactor = 0.25f;//how much to slow by
	int level = 1;//level
	std::vector<SnowParticle*> particles;
	void SpawnParticles();
public:
	//default constructor
	IceProjectile();
	//constructor for easier spawning
	IceProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color , int level = 1);
	//destructor
	~IceProjectile();
	//override to slow the enemy
	void onHit(BaseEnemy* enemy) override;
	
	void Update() override;
	void Render() override;
};

