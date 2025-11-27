#include "HurricaneProjectile.h"
/*!
@file       HurricaneProjectile.cpp
@author     Chew Zavier (c.zavier)
@brief		Contains definition of functions, overrides and variables used by Hurricane Projectiles
*//*_______________________________________________________________________*/
HurricaneProjectile::HurricaneProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color)
{
	HurricaneParticle::LoadImage("Assets/Particles/Wind.png");
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);
	setLifespan(3.0f);
}

HurricaneProjectile::~HurricaneProjectile()
{
	for (auto p : particles)
		delete p;
	particles.clear();
}

void HurricaneProjectile::SpawnParticles()
{
	for (int i = 0; i < 1; ++i)
	{
		CP_Vector vel = CP_Vector_Set(
			((rand() % 20) - 10) * 0.05f,
			((rand() % 20) - 10) * 0.05f
		);

		particles.push_back(new HurricaneParticle(GetLocation(), vel, 10));
	}
}

void HurricaneProjectile::Update()
{
	BaseProjectile::Update();

	SpawnParticles();

	for (auto it = particles.begin(); it != particles.end(); )
	{
		HurricaneParticle* p = *it;
		p->Update();
		if (!p->IsAlive())
		{
			delete p;
			it = particles.erase(it);
		}
		else
			++it;
	}
}

void HurricaneProjectile::Render()
{

	for (auto& p : particles)
		p->Draw();

}
