#pragma once
#include "BaseProjectile.h"

class LavaWall :public virtual BaseProjectile
{
private:
	float hitCD = 0.f;
	float hitMaxCD = 1.f;
public:
	LavaWall(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color);
	~LavaWall();
	void Update() override;
	BaseEnemy* trackedEnemy;
	void Render() override;
	void onHit(BaseEnemy* enemy) override;
};

