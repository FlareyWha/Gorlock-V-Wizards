#pragma once
#include "BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"
#include "IceProjectile.h"
#include "../Particles/SnowParticle.h"
#include <cstdlib>
class IceProjectile: public BaseProjectile
{
private:
	float slowFactor;
	int level;
	std::vector<SnowParticle*> particles;
	void SpawnParticles();
public:
	IceProjectile();
	IceProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color , int level = 1);
	~IceProjectile();
	void onHit(BaseEnemy* enemy) override;
	void Update() override;
	void Render() override;
};

