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
	float radius;

	CP_Color projColor;
	float damage;
	float projectileSpeed;
	float lifespan;
public:
	BaseProjectile(CP_Vector position, CP_Vector direction,float damage,float speed = 150.f, CP_Color color = CP_Color_Create(255, 255, 255, 255));

	void Init();
	void Update();
	void Render();

	float getProjectileDamage();
	float GetLifespan(void);
	CP_Vector GetLocation(void);
	float GetRadius();
	CP_Color getProjColor();
};

