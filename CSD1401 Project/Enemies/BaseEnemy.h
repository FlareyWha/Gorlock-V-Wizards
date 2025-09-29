#pragma once
#include "cprocessing.h"
#include "../../System/Map.h"

enum Direction
{
	UP = 0,
	LEFT,
	RIGHT,
	DOWN
};

class BaseEnemy
{
private:
	int health;
	float speed;
	CP_Image sprite;
	CP_Vector location, directionVector;
	float spriteSize = 48.0f;
	Direction prevDirection;
public:
	int GetHealth(void);
	void SetHealth(int health);
	float GetSpeed(void);
	void SetSpeed(float speed);
	CP_Image GetSprite(void);
	void SetSprite(CP_Image sprite);
	CP_Vector GetLocation(void);
	void SetLocation(float x, float y);
	void SetLocation(CP_Vector location);
	CP_Vector GetDirectionVector(void);
	void SetDirectionVector(float x, float y);
	void SetDirectionVector(CP_Vector direction);
	Direction GetPrevDirection(void);
	void SetPrevDirection(Direction direction);

	void Move(Map* map);
	void Render(void);
};

