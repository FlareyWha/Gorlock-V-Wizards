/*!
@file       BaseEnemy.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains declarations of functions related to the base enemy
*//*_______________________________________________________________________*/

#pragma once
#include "cprocessing.h"
#include "../System/Map.h"
#include <vector>

enum EnemyType
{
	BASIC = 0,
	SPEEDSTER,
	TANK,
	BOSS
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
	float slowFactor = 0.75f;

	float dotTimer = 0.f;
	float maxDOTTimer = 1.f;
	float burnTimer = 0.f;
	float maxBurnTimer = 5.f;
	bool burned = false;
	bool isBurning = false;
	float burnDamage = 0.1f;
	int burnStacks = 0;
public:
	float GetHealth(void);
	void SetHealth(float health);
	float GetMaxHealth(void);
	void SetMaxHealth(float health);

	bool IsSlowed();
	void Slow(bool slow,float slowFactor);

	bool IsBurned();
	void Burn(bool burned);

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

	/**
	 @brief Move the enemy depending on the direction it is going
	 @param map Pointer to a map class
	 @return void
	 */
	void Move(Map* map);
	/**
	 @brief Render the enemy
	 @return void
	 */
	virtual void Render(void);
};

