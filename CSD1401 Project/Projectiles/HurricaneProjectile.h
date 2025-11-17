#pragma once
#include "BaseProjectile.h"
#include "cprocessing.h"
class HurricaneProjectile : public BaseProjectile
{
public:
	HurricaneProjectile(CP_Vector position,CP_Vector direction, float damage,float speed = 150.f,CP_Color color = CP_Color_Create(0,255,0,255));
	~HurricaneProjectile();


};
