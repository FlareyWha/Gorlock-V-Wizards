#include "HomingProjectile.h"
#include<stdio.h>
#include <string.h>
/*!
@file       HomingProjectile.cpp
@author     Chew Zavier (c.zavier)
@brief		Contains defintion of functions, overrides and variables used by HomingProjectile
*//*_______________________________________________________________________*/
void HomingProjectile::setHomingSpeed(float speed)// for setting homing speed
{
	this->homingSpeed = speed;
}

float HomingProjectile::getHomingSpeed()//getting homing speed
{
	return this->homingSpeed;
}
//constructor
HomingProjectile::HomingProjectile(BaseEnemy* specificEnemy, std::vector<BaseEnemy*>* enemyList, CP_Vector initialPos, CP_Vector initialDirection, float damage, float speed, CP_Color color)
{
	this->setDirection(initialDirection);
	this->trackingEnemy = specificEnemy;
	this->setPosition(initialPos);
	this->setProjDamage(damage);
	this->setProjSpeed(speed / 2.f);
	setHomingSpeed(speed);
	this->setProjColor(CP_Color_Create(255, 0, 255, 255));
	this->setProjType(PROJECTILE_TYPE::HOMING);
	timer = initialTimer;
	this->enemyList = enemyList;
	setLifespan(10.f);
}

//overrided update function
void HomingProjectile::Update()
{
	BaseProjectile::Update();//for projectile movement

	timer += -1 * CP_System_GetDt();//"idle" timer
	if (timer <= 0)//once timer clears
	{
		setProjSpeed(getHomingSpeed());//increase speed 
		if (enemyList->empty())
		{
			this->setLifespan(0);//kill this projectile if enemies are all dead
		}
		if (this->trackingEnemy != nullptr)//if this is indeed tracking an enemy
		{
			//find where this enemy is at
			CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(trackingEnemy->GetLocation().x - GetLocation().x, trackingEnemy->GetLocation().y - GetLocation().y));
			setDirection(direction);//start homing towards it
			//if (this->trackingEnemy->GetLocation().x == this->GetLocation().x && this->trackingEnemy->GetLocation().y == this->GetLocation().y)
			//{
			//	this->trackingEnemy = nullptr;
			//	printf("X: %f Y: %f\n", trackingEnemy->GetLocation().x, trackingEnemy->GetLocation().y);
			//}
		}
		else if(this->trackingEnemy == nullptr)//not tracking any enemy at the moment
		{
			
			for (BaseEnemy* enemy : *enemyList)//for each alive enemy
			{
				if (CP_Vector_Distance(enemy->GetLocation(), this->GetLocation()) <= 1000)//check which one is within certain radius
				{
					this->trackingEnemy = enemy;//track this enemy
					break;
				}
			}

		}
	}
	//SpawnParticles();

	for (auto it = particles.begin(); it != particles.end(); )
	{
		WindParticle* p = *it;
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

HomingProjectile::~HomingProjectile()
{
	for (auto p : particles)
		delete p;
	particles.clear();
}

void HomingProjectile::SpawnParticles()
{
	for (int i = 0; i < 2; ++i)
	{
		CP_Vector vel = CP_Vector_Set(
			((rand() % 20) - 10) * 0.05f,
			((rand() % 20) - 10) * 0.05f
		);
		particles.push_back(new WindParticle(GetLocation(), vel, 10));
	}
}

void HomingProjectile::Render()
{
	BaseProjectile::Render();

	for (auto& p : particles)
		p->Draw();
}