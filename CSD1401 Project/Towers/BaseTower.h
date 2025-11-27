/*!
@file       BaseTower.h
@author     Bay Yeok Hao (yeokhao.bay)
@co-author
@brief      This file contains function definitions which child towers will inherit from
*//*_______________________________________________________________________*/

#pragma once
#include <vector>
#include <string>
#include "cprocessing.h"
#include "../Enemies/BaseEnemy.h"
#include "../Projectiles/BaseProjectile.h"
#include "../System/SoundManager.h"
enum class ATTACK_TYPE //the type of attack the tower does
{
	PROJECTILE = 0,
	BEAM,
	HOMING,
	DAMAGEOVERTIME,
	NONE
};

enum class TOWER_TYPE //individual tower types
{
	FIRETOWER = 0,
	ICETOWER,
	LIGHTNINGTOWER,
	WINDTOWER,

	LAVATOWER,
	FROSTTOWER,
	STORMTOWER,
	HURRICANETOWER,

	NONETOWER,

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
	int maxLevel = 3;
	float detectionDistance = 150.f;
	float spriteSize = 48.0f;
	float cooldown = 2.0f;
	float cooldownTime = 0.0f;
	CP_Color color;

	float projSpeed = 150;
	float baseCooldown;
	bool isSlowed = false;
	int levelUpCosts = 150;
	int towerOpacity = 255;

	int baseSaleCosts = 0; // the base price i.e how much the tower costs * 0.85
	int saleCosts = 0; // end sale price
	float maxSecondaryCooldown = 2.f;//max cooldown of secondary spawning of projectiles if needed
	float secondaryCooldown = 0.f;//actual timer for secondary cooldown

	CP_Image towerSprite;
public:
	// Constructor & Deconstructor
	BaseTower();
	~BaseTower();

	// Getters
	CP_Vector getPosition();
	ATTACK_TYPE getAttackType();
	TOWER_TYPE getTowerType();
	CP_Image getImage();
	float getCooldownTime();
	float getCooldown();
	float getDetectionDistance();
	float getDamage();
	int getLevel();
	int getMaxLevel();
	int getUpgradeCosts();
	int getBaseSaleAmt() const;
	int getSaleAmt() const;
	CP_Color getColor();
	float getSpeed();
	float getMaxSecondaryCD();
	float getSecondaryCD();
	bool getSlowed();

	// Setters
	void setPos(float xPosition, float yPosition);
	void setImage(CP_Image inputImage);
	void setTowerType(TOWER_TYPE type);
	void setCooldownTime(float time);
	void setCooldown(float time);
	void setDamage(float damage);
	void setLevel(int level);
	void setMaxLevel(int level);
	void setUpgradeCosts(int cost);
	void setBaseSaleAmt(int amt);
	void setSaleAmt(int amt);
	void setOpacity(int opacity);
	void setColor(CP_Color color);
	void setSpeed(float speed);
	void setMaxSecondaryCD(float maxCD = 2.f);
	void setSecondaryCD(float cd);

	// Other functions
	void virtual levelUp();//level up function
	void Init();
	virtual void Update();
	virtual BaseProjectile* Attack(BaseEnemy* enemy);
	virtual BaseProjectile* SpawnSecondary(BaseEnemy* enemy);// secondary spawning that requires ONLY the specific enemy
	virtual BaseProjectile* SpawnSecondary(std::vector<BaseEnemy*>* enemyList, BaseEnemy* specificEnemy);//secondary spawning that also requires the entire list of enemies
	void Render(void);
	void InitCooldown(float time) { baseCooldown = cooldown = time; }
	void ApplySlowdown(float multiplier);
	void ResetCooldown();
};
