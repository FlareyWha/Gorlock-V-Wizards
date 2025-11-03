#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(10);
	SetMaxHealth(10);
	SetSpeed(100.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Basic.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Basic_Left.png"));
	SetReward(25);
}

BasicEnemy::~BasicEnemy()
{
	CP_Image_Free(GetSprite());
}
