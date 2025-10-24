#pragma once
#include "cprocessing.h"

enum class PROJECTILE_TYPE
{
	PROJECTILE = 0,
	BEAM,
	HOMING,
	DAMAGEOVERTIME,
	NONE
};

class BaseProjectile
{
private:
	PROJECTILE_TYPE projectile = PROJECTILE_TYPE::PROJECTILE;
	CP_Vector direction;
	CP_Vector position;

	float damage;
	float projectileSpeed;
	float lifespan;
public:
	BaseProjectile(CP_Vector position, CP_Vector direction);

	void Init();
	void Update();
	void Render();

	float GetLifespan(void);
};

