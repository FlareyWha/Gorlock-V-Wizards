#include "IceProjectile.h"

IceProjectile::IceProjectile()
{
}

IceProjectile::IceProjectile(CP_Vector position, CP_Vector direction, float damage, float speed, CP_Color color,int level)
{
	SnowParticle::LoadImage("Assets/Particles/Snow.png");
	setProjDamage(damage);
	setProjSpeed(speed);
	setRadius(20.f);
	setPosition(position);
	setDirection(direction);
	setProjColor(color);
	this->level = level;
	setLifespan(5.0f);
}

IceProjectile::~IceProjectile()
{
	for (auto p : particles)
		delete p;
	particles.clear();
}

void IceProjectile::onHit(BaseEnemy* enemy)
{
	enemy->SetHealth(enemy->GetHealth() - this->getProjDamage());
	if (enemy->IsSlowed() == false)
	{ 
		switch (this->level)
		{
		case 1:
			slowFactor = 1.0f;
			break;
		case 2:
			slowFactor = 0.5f;
			break;
		case 3:
			slowFactor = 0.25f;
			break;
		}
		enemy->Slow(true,slowFactor);
	}
}

void IceProjectile::SpawnParticles()
{
	for (int i = 0; i < 1; ++i)
	{
		CP_Vector vel = CP_Vector_Set(
			((rand() % 20) - 10) * 0.05f,
			((rand() % 20) - 10) * 0.05f
		);

		particles.push_back(new SnowParticle(GetLocation(), vel, 10));
	}
}

void IceProjectile::Update()
{
	BaseProjectile::Update();

	SpawnParticles();

	for (auto it = particles.begin(); it != particles.end(); )
	{
		SnowParticle* p = *it;
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

void IceProjectile::Render()
{
	BaseProjectile::Render();

	for (auto& p : particles)
		p->Draw();

}
