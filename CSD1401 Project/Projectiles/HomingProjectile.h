/*!
@file       HomingProjectile.h
@author     Chew Zavier (c.zavier)
@brief		Contains declarations of functions, overrides and variables used by HomingProjectile
*//*_______________________________________________________________________*/

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
	std::vector<BaseEnemy*> *enemyList;//list of enemies currently alive
	void Update() override;//the overrided update function
	BaseEnemy* trackingEnemy = nullptr; // the enemy currently being tracked
	void setHomingSpeed(float speed);//setter
	float getHomingSpeed();//getter
	//constructor
	HomingProjectile(BaseEnemy* specificEnemy, std::vector<BaseEnemy*>* enemyList,CP_Vector initialPos,CP_Vector initialDirection,float damage, float speed, CP_Color color = CP_Color_Create(0,255,0,255));
	//overrided render just for particles
	void Render() override;
	//destructor
	~HomingProjectile();
};

