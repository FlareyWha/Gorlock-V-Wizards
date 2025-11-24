/*!
@file       BaseTower.h
@author     Bay Yeok Hao (yeokhao.bay)
@brief      This file contains function definitions which child towers will inherit from
*//*_______________________________________________________________________*/

#include "BaseTower.h"
#include "cprocessing.h"
#include "../Projectiles/BaseProjectile.h"

//// Constructor
BaseTower::BaseTower()
{
	towerSprite = CP_Image_Load("Assets/Towers/fireTower.png");
	position = CP_Vector_Set(0, 0);
	baseCooldown = 0.f;
	color = CP_Color_Create(0, 0, 0, 255);
}
//
//BaseTower::~BaseTower()
//{
//	CP_Image_Free(towerSprite);
//}

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

TOWER_TYPE BaseTower::getTowerType()
{
	return towerType;
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

float BaseTower::getDamage()
{
	return damage;
}

/*!
@brief      Sets the current tower's position to new values provided as function arguments

This function sets the current X and Y position on the map to specific coordinates provided by the function arguments

@param      int xPosition, int yPosition
@return     none
*//*______________________________________________________________*/
void BaseTower::setPos(float xPosition, float yPosition)
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

void BaseTower::setTowerType(TOWER_TYPE type)
{
	towerType = type;
}

void BaseTower::setCooldownTime(float time)
{
	cooldownTime = time;
}

void BaseTower::setCooldown(float time)
{
	cooldown = time;
	if (baseCooldown <= 0.0f)
		baseCooldown = time;
}

void BaseTower::setDamage(float damage)
{
	this->damage = damage;
}

void BaseTower::setLevel(int level)
{
	this->level = level;
	CP_Math_ClampInt(this->level, 0, 3);
}

void BaseTower::setMaxLevel(int level)
{
	this->maxLevel = level;
}

void BaseTower::levelUp()
{
	if (level != maxLevel)
	{
		this->level++;
		this->setSaleAmt(this->getBaseSaleAmt() + (int)(this->getUpgradeCosts() * 0.9));
		this->setUpgradeCosts(levelUpCosts * level);
		CP_Math_ClampInt(level, 1, maxLevel);
	}
}

int BaseTower::getLevel()
{
	return this->level;
}

int BaseTower::getMaxLevel()
{
	return this->maxLevel;
}

int BaseTower::getUpgradeCosts()
{
	return levelUpCosts;
}

void BaseTower::setUpgradeCosts(int cost)
{
	this->levelUpCosts = cost;
}

int BaseTower::getBaseSaleAmt() const
{
	return this->baseSaleCosts;
}

void BaseTower::setBaseSaleAmt(int amt)
{
	this->baseSaleCosts = amt;
}

int BaseTower::getSaleAmt() const
{
	return saleCosts;
}

void BaseTower::setSaleAmt(int amt)
{
	this->saleCosts = amt;
}

void BaseTower::setOpacity(int opacity)
{
	this->towerOpacity = opacity;
}

CP_Color BaseTower::getColor()
{
	return this->color;
}

void BaseTower::setSpeed(float speed)
{
	this->projSpeed = speed;
}

float BaseTower::getSpeed()
{
	return projSpeed;
}

BaseProjectile* BaseTower::Attack(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new BaseProjectile(this->getPosition(),direction,this->damage,this->projSpeed,this->getColor());
}
BaseProjectile* BaseTower::SpawnSecondary(BaseEnemy* enemy)
{
	CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - getPosition().x, enemy->GetLocation().y - getPosition().y));
	setCooldownTime(getCooldown());
	return new BaseProjectile(this->getPosition(), direction, this->damage, this->projSpeed, this->getColor());
}
BaseProjectile* BaseTower::SpawnSecondary(std::vector<BaseEnemy*>* enemyList,BaseEnemy* specificEnemy)
{
	return nullptr;
}
float BaseTower::getMaxSecondaryCD()
{
	return maxSecondaryCooldown;
}

float BaseTower::getSecondaryCD()
{
	return secondaryCooldown;
}

void BaseTower::setMaxSecondaryCD(float maxCD)
{
	this->maxSecondaryCooldown = maxCD;
}

void BaseTower::setSecondaryCD(float cd)
{
	this->secondaryCooldown = cd;
}


void BaseTower::setColor(CP_Color color)
{
	this->color = color;
}

void BaseTower::Init()
{
}

void BaseTower::Update()
{
	cooldownTime -= 1.f * CP_System_GetDt();
	secondaryCooldown -= 1.f * CP_System_GetDt();
}

void BaseTower::Render()
{
	//CP_Settings_Fill(CP_Color_Create(255,255,255,55));
	//CP_Graphics_DrawCircle(position.x, position.y, detectionDistance * 2.f);
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Image_Draw(towerSprite, position.x, position.y, spriteSize, spriteSize, towerOpacity);

}

void BaseTower::ApplySlowdown(float multiplier)
{
	cooldown = baseCooldown * multiplier;
	isSlowed = true;
}

void BaseTower::ResetCooldown()
{
	cooldown = baseCooldown;
	isSlowed = false;
}

bool BaseTower::slowed() {
	return isSlowed;
}