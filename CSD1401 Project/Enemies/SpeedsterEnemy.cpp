/*!
@file       SpeedsterEnemy.cpp
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains definitions of functions related to the speedster enemy
*//*_______________________________________________________________________*/

#include "SpeedsterEnemy.h"

SpeedsterEnemy::SpeedsterEnemy(CP_Vector location)
{
	// Set default params
	SetLocation(location);
	SetHealth(5.f);
	SetMaxHealth(5.f);
	SetSpeed(200.0f);
	SetMaxSpeed(200.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Speedster.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Speedster_Left.png"));
	SetReward(50);
	SetEnemyType(EnemyType::SPEEDSTER);
}

SpeedsterEnemy::SpeedsterEnemy(CP_Vector location, float speed)
{
	// Set default params
	SetLocation(location);
	SetHealth(5.f);
	SetMaxHealth(5.f);
	SetSpeed(200.0f);
	SetMaxSpeed(speed);
	SetSprite(CP_Image_Load("Assets/Enemies/Speedster.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Speedster_Left.png"));
	SetReward(50);
	SetEnemyType(EnemyType::SPEEDSTER);
}

SpeedsterEnemy::~SpeedsterEnemy()
{
	// Free sprite
	CP_Image_Free(GetSprite());
}
