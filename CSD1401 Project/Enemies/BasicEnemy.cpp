#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(10);
	SetSpeed(50.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Basic.png"));
	SetPath(Map::GetInstance(), location, location);
}

BasicEnemy::~BasicEnemy()
{
	CP_Image_Free(GetSprite());
}
