#pragma once
#include "cprocessing.h"
#include "../../System/Map.h"
#include <vector>

class BaseEnemy
{
protected:
	int health, maxHealth;
	float speed;
	CP_Image sprite, spriteLeft;
	CP_Vector location, directionVector;
	float spriteSize = 50.0f;
	int pathId = 0;
	int reward;
public:
	int GetHealth(void);
	void SetHealth(int health);
	int GetMaxHealth(void);
	void SetMaxHealth(int health);
	int GetReward(void);
	void SetReward(int rewardAmt);
	float GetSpeed(void);
	void SetSpeed(float speed);
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
	void Move(Map* map);
	virtual void Render(void);
	void RenderBoss(void);
};

