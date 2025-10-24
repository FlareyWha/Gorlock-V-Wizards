#include "SpeedsterEnemy.h"

SpeedsterEnemy::SpeedsterEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(5);
	SetSpeed(200.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Speedster.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Speedster_Left.png"));
	SetPath(Map::GetInstance(), location, location);
}

SpeedsterEnemy::~SpeedsterEnemy()
{
	CP_Image_Free(GetSprite());
}
