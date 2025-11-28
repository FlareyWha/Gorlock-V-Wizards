/*!
@file       LavaWall.h
@author     Chew Zavier (c.zavier)
@brief		Contains declarations of functions, overrides and variables used by LavaWall
*//*_______________________________________________________________________*/

#pragma once
#include "BaseProjectile.h"
#include "../Particles/FireParticle.h"
#include "cprocessing.h"
#include <vector>

class LavaWall :public BaseProjectile
{
private:
	float sfxTimer = 0.f, sfxMaxTimer = 1.f;
	std::vector<FireParticle*> particles;
	void SpawnParticles();

public:
	// Constructor & Deconstructor
	LavaWall(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~LavaWall();

	// overriden functions
	void Update() override;
	void Render() override;
	void onHit(BaseEnemy* enemy) override;
};

