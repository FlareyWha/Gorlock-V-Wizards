/*!
@file       BaseTower.h
@author     Bay Yeok Hao (yeokhao.bay)
@brief      This file contains functions to create a Base Tower which other towers will inherit from
*//*_______________________________________________________________________*/

#pragma once
#include <vector>
#include <string>
#include "cprocessing.h"
#include "../Enemies/BaseEnemy.h"
#include "../../Projectiles/BaseProjectile.h"
enum class ATTACK_TYPE
{
	PROJECTILE = 0,
	BEAM,
	HOMING,
	DAMAGEOVERTIME,
	NONE
};

enum class TOWER_TYPE
{
	FIRETOWER = 0,
	ICETOWER,
	LIGHTNINGTOWER,
	WINDTOWER,

	LAVATOWER,
	FROSTTOWER,
	STORMTOWER,
	HURRICANETOWER,

	BASETOWER

};

class BaseTower
{
protected:
	TOWER_TYPE towerType = TOWER_TYPE::BASETOWER;
	CP_Vector position;
	ATTACK_TYPE attack = ATTACK_TYPE::NONE;
	float damage = 0;
	int level = 1;
	float detectionDistance = 150.f;
	float spriteSize = 48.0f;
	float cooldown = 2.0f;
	float cooldownTime = 0.0f;
	CP_Color color;
	float projSpeed = 150;
	float baseCooldown;
public:
	CP_Image towerSprite;

	//BaseTower();
	//~BaseTower();

	// Getters
	CP_Vector getPosition();
	ATTACK_TYPE getAttackType();
	TOWER_TYPE getTowerType();
	CP_Image getImage();
	float getCooldownTime();
	float getCooldown();
	float getDetectionDistance();

	float getDamage();
	// Setters
	void setPos(int xPosition, int yPosition);
	void setImage(CP_Image inputImage);
	void setTowerType(TOWER_TYPE type);
	void setCooldownTime(float time);
	void setCooldown(float time);

	void setDamage(float damage);

	void setLevel(int level);
	int getLevel();

	void setColor(CP_Color color);
	CP_Color getColor();

	void setSpeed(float speed);
	float getSpeed();
	// Other functions
	void Init();
	void Update();
	virtual BaseProjectile* Attack(BaseEnemy* enemy);

	void Render(void);
	void InitCooldown(float time) { baseCooldown = cooldown = time; }
	void ApplySlowdown(float multiplier);
	void ResetCooldown();
	bool slowed = false;
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