/*!
@file       Game.h
@author     Chew Zavier(c.zavier)
@brief      This file contains functions to draw the Game Interface.
*//*_______________________________________________________________________*/

#pragma once
#include "cprocessing.h"
#include <string>
enum currSelected {
	FIRETOWER,
	WINDTOWER,
	ICETOWER,
	LIGHTNINGTOWER,
	NONE_TOWER
};
typedef struct TowerUIs {
	int towerCost;
	CP_Vector pos;
	float size = 96.f;
	CP_Image image;
	float radius = size / 2.0f;
	currSelected selection = currSelected::NONE_TOWER;
	float opacity = 255.f;
}Tower;
class Game{
private:
	int maxHealth = 3;
	int health = 3;
	float fontSize = 12.0f;
	int moneys = 0;

	float imageScaling = 4.0f;
	CP_Vector spawnLocation = CP_Vector_Set(24.0f, 24.0f);
public:
	void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle = 0.0f, float cornerRadius = 0.0f, CP_Color rectColor = { 100,100,100,255 });
	void drawText(const char* text, float xPos, float yPos);

	void setFontSize(float size);
	float getFontSize();

	int getMoneys();
	void setMoneys(int moneyAmt);
	void loseMoneys(int moneyAmt);
	void gainMoneys(int moneyAmt);
	void drawMoneys(float x,float y);



	void drawHeart(float x,float y);
	int getHealth();
	int getMaxHealth();
	void setMaxHealth(int max);
	void setHealth(int hp);
	void takeDamage(int hp);

	CP_Vector getSpawnLocation();

	int heartOpacity = 155;
	float heartBeatStart = 0.25f;
	float heartBeatTimer = heartBeatStart;
	float heartBeatScale = 1.0f;
	float startOfTimer = 1.75f;
	float timer = startOfTimer;

	CP_Image healthImage;
	CP_Image emptyHeartImage;
	CP_Image moneysImage;
	currSelected currSelect = currSelected::NONE_TOWER;

	Tower fireTowerUI;
	Tower iceTowerUI;
	Tower windTowerUI;
	Tower lightningTowerUI;

	Tower uiElements[4];
};
void gameInit(void);
void gameUpdate(void);
void gameExit(void);



