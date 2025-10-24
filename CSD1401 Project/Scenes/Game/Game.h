/*!
@file       Game.h
@author     Chew Zavier(c.zavier)
@brief      This file contains functions to draw the Game Interface.
*//*_______________________________________________________________________*/

#pragma once
#include "cprocessing.h"
#include <string>
class Game{
private:
	int maxHealth = 3;
	int health = 3;
	float fontSize = 12.0f;
	int moneys = 0;

	float imageScaling = 8.0f;
public:
	void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle = 0.0f, float cornerRadius = 0.0f, CP_Color rectColor = { 100,100,100,255 });
	void drawText(const char* text, float xPos, float yPos);

	void setFontSize(float size);
	float getFontSize();

	int getMoneys();
	void setMoneys(int moneyAmt);
	void loseMoneys(int moneyAmt);
	void gainMoneys(int moneyAmt);

	void drawHeart(float x,float y);

	int getHealth();
	int getMaxHealth();
	void setMaxHealth(int max);
	void setHealth(int hp);
	void takeDamage(int hp);
	CP_Image healthImage;
	CP_Image emptyHeartImage;
	CP_Image fireTowerImage;
};
void gameInit(void);
void gameUpdate(void);
void gameExit(void);



