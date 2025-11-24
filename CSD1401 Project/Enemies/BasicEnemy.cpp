/*!
@file       BasicEnemy.cpp
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains definitions of functions related to the basic enemy
*//*_______________________________________________________________________*/

#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(CP_Vector location)
{
	// Set default params
	SetLocation(location);
	SetHealth(10.0f);
	SetMaxHealth(10.0f);
	SetSpeed(100.0f);
	SetMaxSpeed(100.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Basic.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Basic_Left.png"));
	SetReward(25);
	SetEnemyType(EnemyType::BASIC);
}

BasicEnemy::~BasicEnemy()
{
	// Free sprite
	CP_Image_Free(GetSprite());
}
