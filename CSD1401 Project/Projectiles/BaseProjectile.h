#pragma once
#include "cprocessing.h"
#include "../Enemies/BaseEnemy.h"
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
	BaseProjectile();
	BaseProjectile(CP_Vector position, CP_Vector direction,float damage,float speed = 150.f, CP_Color color = CP_Color_Create(255, 255, 255, 255));

	void Init();
	void Update();
	void Render();

	float getProjDamage();
	float getProjectileDamage();
	float GetLifespan(void);
	CP_Vector GetLocation(void);
	float GetRadius();
	CP_Color getProjColor();

	void setProjDamage(float damage);
	void setProjSpeed(int speed);
	void setPosition(CP_Vector pos);
	void setRadius(float rad);
	void setProjColor(CP_Color color);
	void setDirection(CP_Vector dir);
	void setLifespan(float lifespan);
	void virtual onHit(BaseEnemy* enemy);
};

