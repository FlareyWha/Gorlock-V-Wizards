#pragma once
#include "BaseProjectile.h"
#include "../Particles/FireParticle.h"
#include "cprocessing.h"
#include <vector>
/*!
@file       LavaWall.h
@author     Chew Zavier (c.zavier)
@brief		Contains declaration of functions, overrides and variables used by LavaWall
*//*_______________________________________________________________________*/
class LavaWall :public BaseProjectile
{
private:
	float sfxTimer = 0.f, sfxMaxTimer = 1.f;
	std::vector<FireParticle*> particles;
	void SpawnParticles();

public:
	LavaWall(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~LavaWall();
	void Update() override;
	void Render() override;
	void onHit(BaseEnemy* enemy) override;
};

