#pragma once
#include "BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"
#include "../Particles/WindParticle.h"
#include "cprocessing.h"
#include <vector>
class HomingProjectile : public BaseProjectile
{
private:
	float timer = 3.f;
	float initialTimer = .5f;

	float homingSpeed;

	std::vector<WindParticle*> particles;
	void SpawnParticles();

public:
	std::vector<BaseEnemy*> *enemyList;
	void Update() override;
	BaseEnemy* trackingEnemy;
	void setHomingSpeed(float speed);
	float getHomingSpeed();
	HomingProjectile(BaseEnemy* specificEnemy, std::vector<BaseEnemy*>* enemyList,CP_Vector initialPos,CP_Vector initialDirection,float damage, float speed, CP_Color color = CP_Color_Create(0,255,0,255));
	void Render() override;
	~HomingProjectile();
};

