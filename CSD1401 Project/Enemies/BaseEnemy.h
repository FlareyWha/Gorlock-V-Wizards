#pragma once
#include "cprocessing.h"
#include "../../System/Map.h"
#include <vector>

enum EnemyType
{
	BASIC = 0,
	SPEEDSTER,
	TANK
};

class BaseEnemy
{
protected:
	float health, maxHealth;
	float speed , maxSpeed;
	CP_Image sprite, spriteLeft;
	CP_Vector location, directionVector;
	float spriteSize = 50.0f;
	int pathId = 0;
	int reward;
	EnemyType type;

	float slowTimer = 0.f;
	float maxSlowTimer = 3.f;
	bool slowed = false;
public:
	float GetHealth(void);
	void SetHealth(float health);
	float GetMaxHealth(void);
	void SetMaxHealth(float health);

	bool IsSlowed();
	void Slow(bool slow);

	int GetReward(void);
	void SetReward(int rewardAmt);

	float GetSpeed(void);
	void SetSpeed(float speed);
	float GetMaxSpeed(void);
	void SetMaxSpeed(float maxSpeed);

	float GetSpriteSize();
	CP_Image GetSprite(void);
	void SetSprite(CP_Image sprite);
	CP_Image GetSpriteLeft(void);
	void SetSpriteLeft(CP_Image sprite);
	CP_Vector GetLocation(void);
	void SetLocation(float x, float y);
	void SetLocation(CP_Vector location);
	CP_Vector GetDirectionVector(void);
	void SetDirectionVector(float x, float y);
	void SetDirectionVector(CP_Vector direction);
	EnemyType GetEnemyType(void);
	void SetEnemyType(EnemyType type);

	void Move(Map* map);
	virtual void Render(void);
};

