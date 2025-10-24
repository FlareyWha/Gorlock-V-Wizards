#include "TankEnemy.h"

TankEnemy::TankEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(100);
	SetSpeed(25.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Tank.png"));
	SetPath(Map::GetInstance(), location, location);
}

TankEnemy::~TankEnemy()
{
	CP_Image_Free(GetSprite());
}
