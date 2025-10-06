/*!
@file       BaseTower.h
@author     Bay Yeok Hao (yeokhao.bay)
@brief      This file contains functions to create a Base Tower which other towers will inherit from
*//*_______________________________________________________________________*/

#pragma once
#include <string>
#include "cprocessing.h"

enum class ATTACK_TYPE
{
	PROJECTILE = 0,
	BEAM,
	HOMING,
	DAMAGEOVERTIME,
	NONE
};

class BaseTower
{
private:
	std::string towerName = "baseTower";
	CP_Vector position;
	ATTACK_TYPE attack = ATTACK_TYPE::NONE;
	int damage = 0;
	int level = 1;
	float attackSpeed, range = 0.0f;
	CP_Image towerSprite;
	float spriteSize = 48.0f;

public:

	BaseTower();

	// Getters
	CP_Vector getPosition();
	ATTACK_TYPE getAttackType();
	std::string getName();
	CP_Image getImage();

	// Setters
	void setPos(int xPosition, int yPosition);
	void setImage(CP_Image inputImage);

	// Other functions
	void Init();
	void Update();
	void AttackEnemy(void);

	void Render(void);
};

/*
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
*/