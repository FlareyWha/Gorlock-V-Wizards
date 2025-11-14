#pragma once
#include "BaseProjectile.h"
#include "../Enemies/BaseEnemy.h"
#include "cprocessing.h"
class HomingProjectile : public virtual BaseProjectile
{
private:
	float timer = 3.f;
	float initialTimer = .5f;

	float homingSpeed;
public:
	void Update() override;
	BaseEnemy* trackingEnemy;
	void setHomingSpeed(float speed);
	float getHomingSpeed();
	HomingProjectile(BaseEnemy* enemy,CP_Vector initialPos,CP_Vector initialDirection,float damage, float speed, CP_Color color = CP_Color_Create(0,255,0,255));
};

