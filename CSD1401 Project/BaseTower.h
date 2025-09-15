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
	int xPos, yPos;
	ATTACK_TYPE attack = ATTACK_TYPE::NONE;
	int damage = 0;
	int level = 1;
	float attackSpeed, range = 0.0f;
	CP_Image towerSprite;

public:

	BaseTower();

	// Getters
	int getXPos();
	int getYPos();
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
};

