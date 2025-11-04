#include "BaseProjectile.h"
#include "cprocessing.h"
#include <iostream>

BaseProjectile::BaseProjectile()
{
	this->damage = 1.f;
}

BaseProjectile::BaseProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	this->damage = damage;
	this->projectileSpeed = speed;
	radius = 20.f;
	this->position = position;
	this->direction = direction;
	this->projColor = color;

	lifespan = 5.0f;
}

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

void BaseProjectile::setProjDamage(float damage)
{
	this->damage = damage;
}

void BaseProjectile::setProjSpeed(int speed)
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

void BaseProjectile::onHit(BaseEnemy* enemy)
{
	enemy->SetHealth(enemy->GetHealth() - damage);
}
