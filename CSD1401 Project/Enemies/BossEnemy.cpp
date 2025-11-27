#include "BossEnemy.h"
#include "cprocessing.h"

/*!
@file       BossEnemy.cpp
@author     Chee Kang(l.cheekang)
@brief      This file contains the function definitions for the BossEnemy class
*//*_______________________________________________________________________*/

BossEnemy::BossEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(200.0f);
	SetMaxHealth(200.0f);
	SetSpeed(25.0f);
	SetMaxSpeed(25.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Boss.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Boss_Left.png"));
	SetReward(10000);
	SetEnemyType(EnemyType::BOSS);
}

/**
 @brief Will render the boss enemy
 @param void
 @return void
 */

void BossEnemy::Render(void)
{
	if (directionVector.x >= 0)
		CP_Image_Draw(sprite, location.x, location.y, spriteSize, spriteSize, 255);
	else if (directionVector.x <= 0)
		CP_Image_Draw(spriteLeft, location.x, location.y, spriteSize, spriteSize, 255);

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(location.x, location.y - spriteSize * 0.5f, (float)health / (float)maxHealth * 50.f, 10.f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 5));
	CP_Graphics_DrawCircle(location.x, location.y, 155);
}

/**
 @brief	Frees the memory allocated for the boss enemy sprite
 @return void
 */
BossEnemy::~BossEnemy()
{
	CP_Image_Free(GetSprite());
}



