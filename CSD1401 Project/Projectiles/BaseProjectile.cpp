#include "BaseProjectile.h"
#include "cprocessing.h"
#include <iostream>

BaseProjectile::BaseProjectile(CP_Vector position, CP_Vector direction)
{
	damage = 1.f;
	projectileSpeed = 150.f;
	radius = 20.f;
	this->position = position;
	this->direction = direction;
	
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
	CP_Graphics_DrawCircle(position.x, position.y, 15.f);
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
