#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(10);
	SetSpeed(500.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Basic.png"));
}

BasicEnemy::~BasicEnemy()
{
	CP_Image_Free(GetSprite());
}
