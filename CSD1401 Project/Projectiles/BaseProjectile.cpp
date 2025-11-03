#include "BaseProjectile.h"
#include "cprocessing.h"
#include <iostream>

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
