/*!
@file       HurricaneTower.h
@author     Chew Zavier (c.zavier)
@brief		Contains declaration of functions, overrides and variables used by HurricaneTower.cpp
*//*_______________________________________________________________________*/
#pragma once
#include "BaseTower.h"
#include "cprocessing.h"
class HurricaneTower : public BaseTower
{
private: 

public:
	HurricaneTower(CP_Vector position);//constructor
	~HurricaneTower();//destructor

	BaseProjectile* Attack(BaseEnemy* enemy) override;//attack override but return hurricane projectile instead
	BaseProjectile* SpawnSecondary(std::vector<BaseEnemy*>* enemyList,BaseEnemy* specificEnemy) override;//to spawn the homing missles
};

