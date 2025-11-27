#pragma once
#include "BaseProjectile.h"
#include "cprocessing.h"
#include "../Particles/HurricaneParticle.h"
/*!
@file       HurricaneProjectile.h
@author     Chew Zavier (c.zavier)
@brief		Contains declaration of functions, overrides and variables used by HurricaneProjectile.cpp
*//*_______________________________________________________________________*/
class HurricaneProjectile : public BaseProjectile
{
protected:
	std::vector<HurricaneParticle*> particles;
	void SpawnParticles();
public:
	//constructor
	HurricaneProjectile(CP_Vector position,CP_Vector direction, float damage,float speed = 150.f,CP_Color color = CP_Color_Create(0,255,0,255));
	//destructor
	~HurricaneProjectile();
	void Update() override;
	void Render() override;

};
