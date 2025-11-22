#pragma once
#include "BaseProjectile.h"
#include "../Particles/FireParticle.h"
#include "cprocessing.h"
#include <vector>

class LavaWall :public BaseProjectile
{
private:
	float hitCD = 0.f;
	float hitMaxCD = 1.f;
	float sfxTimer = 0.f, sfxMaxTimer = 1.f;
	std::vector<FireParticle*> particles;
	void SpawnParticles();

public:
	LavaWall(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~LavaWall();
	void Update() override;
	BaseEnemy* trackedEnemy;
	void Render() override;
	void onHit(BaseEnemy* enemy) override;
};

