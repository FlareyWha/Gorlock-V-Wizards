#include "SpeedsterEnemy.h"

SpeedsterEnemy::SpeedsterEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(5);
	SetMaxHealth(5);
	SetSpeed(200.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Speedster.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Speedster_Left.png"));
	SetReward(50);
	SetEnemyType(EnemyType::SPEEDSTER);
}

SpeedsterEnemy::~SpeedsterEnemy()
{
	CP_Image_Free(GetSprite());
}
