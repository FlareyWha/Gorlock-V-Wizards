#pragma once
#include "cprocessing.h"
#include "../../System/Map.h"
#include <vector>

class BaseEnemy
{
private:
	int health, maxHealth;
	float speed;
	CP_Image sprite, spriteLeft;
	CP_Vector location, directionVector;
	float spriteSize = 50.0f;
	int pathId = 0;
public:
	int GetHealth(void);
	void SetHealth(int health);
	int GetMaxHealth(void);
	void SetMaxHealth(int health);
	float GetSpeed(void);
	void SetSpeed(float speed);
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
	void Render(void);
};

