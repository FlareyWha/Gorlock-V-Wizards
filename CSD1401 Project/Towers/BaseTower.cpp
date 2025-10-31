/*!
@file       BaseTower.h
@author     Bay Yeok Hao (yeokhao.bay)
@brief      This file contains function definitions which child towers will inherit from
*//*_______________________________________________________________________*/

#include "BaseTower.h"
#include "cprocessing.h"
#include "../Projectiles/BaseProjectile.h"

// Constructor
BaseTower::BaseTower()
{
	//towerSprite = CP_Image_Load("Assets/Towers/fireTower.png");
	position = CP_Vector_Set(0, 0);
}

BaseTower::~BaseTower()
{
	CP_Image_Free(towerSprite);
}

CP_Vector BaseTower::getPosition()
{
	return position;
}

/*!
@brief      Gets the enum of the tower

This function returns the specified enum type of attack the tower will perform

@param      void
@return     enum ATTACK_TYPE
*//*______________________________________________________________*/
ATTACK_TYPE BaseTower::getAttackType()
{
	return attack;
}

/*!
@brief      Gets the name of the tower on the grid

This function returns the name of the tower

@param      void
@return     string
*//*______________________________________________________________*/
std::string BaseTower::getName()
{
	return towerName;
}

/*!
@brief      Gets the current image corresponding to the tower

This function gets the tower's sprite

@param      void
@return     CP_Image
*//*______________________________________________________________*/
CP_Image BaseTower::getImage()
{
	return towerSprite;
}

float BaseTower::getCooldownTime()
{
	return cooldownTime;
}

float BaseTower::getCooldown()
{
	return cooldown;
}

float BaseTower::getDetectionDistance()
{
	return detectionDistance;
}

int BaseTower::getDamage()
{
	return damage;
}

/*!
@brief      Sets the current tower's position to new values provided as function arguments

This function sets the current X and Y position on the map to specific coordinates provided by the function arguments

@param      int xPosition, int yPosition
@return     none
*//*______________________________________________________________*/
void BaseTower::setPos(int xPosition, int yPosition)
{
	position = CP_Vector_Set(xPosition, yPosition);
}

/*!
@brief      Sets the current tower's image to provided image

This function sets the tower's sprite to the CP_Image in the function argument

@param      CP_Image inputImage
@return     none
*//*______________________________________________________________*/
void BaseTower::setImage(CP_Image inputImage)
{
	towerSprite = inputImage;
}

void BaseTower::setCooldownTime(float time)
{
	cooldownTime = time;
}

void BaseTower::setCooldown(float time)
{
	cooldown = time;
}

void BaseTower::setDamage(int damage)
{
	this->damage = damage;
}

BaseProjectile* BaseTower::Attack(CP_Vector direction)
{
	setCooldownTime(getCooldown());
	return new BaseProjectile(getPosition(), direction);
}

void BaseTower::Init()
{
}

void BaseTower::Update()
{
	cooldownTime -= 1.f * CP_System_GetDt();
}

void BaseTower::Render()
{
	CP_Image_Draw(towerSprite, position.x, position.y, spriteSize, spriteSize, 255);
}