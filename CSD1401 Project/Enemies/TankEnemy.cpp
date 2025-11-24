/*!
@file       TankEnemy.cpp
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains definitions of functions related to the tank enemy
*//*_______________________________________________________________________*/

#include "TankEnemy.h"

TankEnemy::TankEnemy(CP_Vector location)
{
	// Set default params
	SetLocation(location);
	SetHealth(100.f);
	SetMaxHealth(100.f);
	SetSpeed(50.0f);
	SetMaxSpeed(50.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Tank.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Tank_Left.png"));
	SetReward(100);
	SetEnemyType(EnemyType::TANK);
}

TankEnemy::~TankEnemy()
{
	// Free sprite
	CP_Image_Free(GetSprite());
}
