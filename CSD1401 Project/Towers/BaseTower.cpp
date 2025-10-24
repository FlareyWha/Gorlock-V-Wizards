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
	towerSprite = CP_Image_Load("Assets/kenney_tiny-battle/Tiles/tile_0068.png");
	attackSpeed = 1;
	position = CP_Vector_Set(0, 0);
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

// testing for now
void BaseTower::AttackEnemy(void)
{
	OutputDebugString("attacking enemy now\n");

	
}

// zzzzzz
void BaseTower::Init()
{
}

void BaseTower::Update()
{

}

void BaseTower::Render()
{
	CP_Image_Draw(towerSprite, position.x, position.y, spriteSize, spriteSize, 255);
}