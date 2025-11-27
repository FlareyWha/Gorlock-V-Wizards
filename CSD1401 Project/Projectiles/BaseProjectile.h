/*!
@file       BaseProjectile.h
@author     Bay Yeok Hao (yeokhao.bay)
@brief		Contains definitions of functions, overrides and variables used by BaseProjectile
			All other projectiles will inherit from this class
*//*_______________________________________________________________________*/

#pragma once
#include "cprocessing.h"
#include "../Enemies/BaseEnemy.h"
#include <vector>

enum class PROJECTILE_TYPE //different types of projectiles
{
	PROJECTILE = 0,
	BEAM,
	HOMING,
	DAMAGEOVERTIME,
	CHAIN,
	NONE
};

class BaseProjectile
{
protected:
	PROJECTILE_TYPE projectile = PROJECTILE_TYPE::PROJECTILE;
	CP_Vector direction = CP_Vector_Set(0.f,0.f);
	CP_Vector position = CP_Vector_Set(0.f, 0.f);
	float radius = 20.f;;

	CP_Color projColor = CP_Color_Create(255, 255, 255, 255);
	float damage = 1.f;
	float projectileSpeed = 1.f;
	float lifespan = 2.0f;
public:
	// Constructor, overloaded version for easy spawning by tower
	BaseProjectile();
	BaseProjectile(CP_Vector position, CP_Vector direction,float damage,float speed = 150.f, CP_Color color = CP_Color_Create(255, 255, 255, 255));

	// Getters
	float getProjDamage();
	float getProjectileDamage();
	float GetLifespan(void);
	CP_Vector GetLocation(void);
	float GetRadius();
	CP_Color getProjColor();
	PROJECTILE_TYPE getProjType();
	CP_Vector getDirection();
	
	// Setters
	void setProjType(PROJECTILE_TYPE type);
	void setProjDamage(float damage);
	void setProjSpeed(float speed);
	void setPosition(CP_Vector pos);
	void setRadius(float rad);
	void setProjColor(CP_Color color);
	void setDirection(CP_Vector dir);
	void setLifespan(float lifespan);

	// Other functions
	void Init();
	virtual void Update();
	virtual void Render();
	void virtual onHit(BaseEnemy* enemy);//on hit function to easily call when projectile touches enemy
	void virtual chainHit(std::vector<BaseEnemy*> enemyList,BaseEnemy* specificEnemy);//specifically for lightning projectile
};

