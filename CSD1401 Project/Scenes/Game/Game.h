/*!
@file       Game.h
@author     Chew Zavier(c.zavier)
@brief      This file contains functions to draw the Game Interface.
*//*_______________________________________________________________________*/

#pragma once
#include "cprocessing.h"
#include "../../System/WaveManager.h"
#include "../../Towers/BaseTower.h"	
#include "../../Utils/Button.h"
#include <string>

enum
{
	HOW_TO_PLAY_SIZE = 8,
};

enum currSelected {
	FIRETOWER = 0,
	WINDTOWER,
	ICETOWER,
	LIGHTNINGTOWER,
	LEVELUP,
	MERGE,
	SELLING,
	NONE_TOWER
};
typedef struct TowerUIs {
	int towerCost = 0;
	CP_Vector pos = CP_Vector_Set(0,0);
	float size = 96.f;
	CP_Image image;
	float radius = size / 2.0f;
	currSelected selection = currSelected::NONE_TOWER;
	int opacity = 255;
}Tower;
class Game
{
private:
	int maxHealth = 3;
	int health = 3;
	float fontSize = 12.0f;
	int moneys = 500;
	Button* quit;
	Button* settings;

	float imageScaling = 6.0f;
	bool winScreen = false;
	bool loseScreen = false;
	bool paused = false;

public:
	void PauseGame() { paused = true; }
	void ResumeGame() { paused = false; }
	void SetPaused(bool p) { paused = p; }
	bool IsPaused() const { return paused; }
	void CleanUpGame();

	void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle = 0.0f, float cornerRadius = 0.0f, CP_Color rectColor = { 100,100,100,255 });
	void drawText(const char* text, float xPos, float yPos);

	void setFontSize(float size);
	float getFontSize();

	int getMoneys();
	void setMoneys(int moneyAmt);
	void loseMoneys(int moneyAmt);
	void gainMoneys(int moneyAmt);
	void drawMoneys(float x,float y);

	void ButtonInit();
	void ButtonDraw();

	void drawHeart(float x,float y);
	int getHealth(void);
	int getMaxHealth(void);
	void setMaxHealth(int max);
	void setHealth(int hp);
	void takeDamage(int hp);

	int heartOpacity = 155;
	float heartBeatStart = 0.25f;
	float heartBeatTimer = heartBeatStart;
	float heartBeatScale = 1.0f;
	float startOfTimer = 1.75f;
	float timer = startOfTimer;

	CP_Image healthImage;
	CP_Image emptyHeartImage;
	CP_Image moneysImage;
	CP_Image howToPlayImages[HOW_TO_PLAY_SIZE];
	currSelected currSelect = currSelected::NONE_TOWER;

	Tower fireTowerUI;
	Tower iceTowerUI;
	Tower windTowerUI;
	Tower lightningTowerUI;
	Tower levelUpUI;
	Tower mergeUI;
	Tower sellingUI;

	bool grabbingTower = false;

	BaseTower* currentTower = nullptr;

	Tower uiElements[7];

	WaveManager* waveManager;
	Button* nextWave;
	Button* back;
	Button* howToPlayNext;
	Button* howToPlayBack;
	Button* howToPlayEnd;

	bool howToPlayActive = true;
	int howToPlayCurrentIndex = 0;

	bool shouldShowWinscreen(void);
	bool shouldShowLosescreen(void);
	void setWin(bool win);
	void setLose(bool lose);

	void updateHowToPlayScreen(void);
	void renderHowToPlayScreen(void);

	void disableHowToPlayScreen(void);
};
void gameInit(void);
void gameUpdate(void);
void gameExit(void);



