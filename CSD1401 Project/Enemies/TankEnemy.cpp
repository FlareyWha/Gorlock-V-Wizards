#include "TankEnemy.h"

TankEnemy::TankEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(100);
	SetSpeed(50.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Tank.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Tank_Left.png"));
	SetPath(Map::GetInstance(), location, location);
}

TankEnemy::~TankEnemy()
{
	CP_Image_Free(GetSprite());
}
