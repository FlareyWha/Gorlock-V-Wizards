/*!
@file       BaseProjectile.cpp
@author     Bay Yeok Hao (yeokhao.bay)
@brief		Contains declarations of functions, overrides and variables used by BaseProjectile
			All other projectiles will inherit from this class
*//*_______________________________________________________________________*/

#include "BaseProjectile.h"
#include "cprocessing.h"

// Constructor
BaseProjectile::BaseProjectile()
{
}

// Overloaded constructor with params for easy spawning by tower
BaseProjectile::BaseProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	this->damage = damage;
	this->projectileSpeed = speed;
	radius = 20.f;
	this->position = position;
	this->direction = direction;
	this->projColor = color;
	
	lifespan = 2.0f;
}

// Getters
float BaseProjectile::getProjDamage()
{
	return damage;
}

float BaseProjectile::getProjectileDamage()
{
	return damage;
}

float BaseProjectile::GetLifespan()
{
	return lifespan;
}

CP_Vector BaseProjectile::GetLocation()
{
	return position;
}

float BaseProjectile::GetRadius()
{
	return radius;
}
CP_Color BaseProjectile::getProjColor()
{
	return projColor;
}

PROJECTILE_TYPE BaseProjectile::getProjType()
{
	return projectile;
}

CP_Vector BaseProjectile::getDirection()
{
	return direction;
}

// Setters
void BaseProjectile::setProjType(PROJECTILE_TYPE type)
{
	this->projectile = type;
}

void BaseProjectile::setProjDamage(float damage)
{
	this->damage = damage;
}

void BaseProjectile::setProjSpeed(float speed)
{
	this->projectileSpeed = speed;
}

void BaseProjectile::setPosition(CP_Vector pos)
{
	this->position = pos;
}

void BaseProjectile::setRadius(float rad)
{
	this->radius = rad;
}

void BaseProjectile::setProjColor(CP_Color color)
{
	this->projColor = color;
}

void BaseProjectile::setDirection(CP_Vector dir)
{
	this->direction = dir;
}

void BaseProjectile::setLifespan(float lifespan)
{
	this->lifespan = lifespan;
}

// Other functions
void BaseProjectile::Init()
{
}

void BaseProjectile::Update()
{
	lifespan -= 1.f * CP_System_GetDt();
	position = CP_Vector_Add(position, CP_Vector_Scale(direction, projectileSpeed * CP_System_GetDt()));
}

void BaseProjectile::Render()
{
	CP_Settings_Fill(projColor);
	CP_Graphics_DrawCircle(position.x, position.y, 15.f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
}

void BaseProjectile::onHit(BaseEnemy* enemy)
{
	enemy->SetHealth(enemy->GetHealth() - this->getProjDamage());
}

void BaseProjectile::chainHit(std::vector<BaseEnemy*> enemyList,BaseEnemy* specificEnemy)
{
}
