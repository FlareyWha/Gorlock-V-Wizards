#include "SpeedsterEnemy.h"

SpeedsterEnemy::SpeedsterEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(5.f);
	SetMaxHealth(5.f);
	SetSpeed(200.0f);
	SetMaxSpeed(200.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Speedster.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Speedster_Left.png"));
	SetReward(50);
	SetEnemyType(EnemyType::SPEEDSTER);
	RandomizeTurn();
}

SpeedsterEnemy::~SpeedsterEnemy()
{
	CP_Image_Free(GetSprite());
}
