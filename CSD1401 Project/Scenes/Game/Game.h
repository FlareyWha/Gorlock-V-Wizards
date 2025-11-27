/*!
@file       Game.h
@author     Team The Hardest Thing
@brief      This file contains declarations for functions and variables for Game.cpp
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

enum currSelected {//what the user has selected in the UI
	FIRETOWER = 0,
	WINDTOWER,
	ICETOWER,
	LIGHTNINGTOWER,
	LEVELUP,
	MERGE,
	SELLING,
	NONE_TOWER
};

typedef struct TowerUIs {//UI icons
	int towerCost = 0;
	CP_Vector pos = CP_Vector_Set(0,0);
	float size = 96.f;
	CP_Image image = CP_Image_Load("./Assets/Towers/fireTower.png");
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

	//drawRect just to make it easier to use with color
	void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle = 0.0f, float cornerRadius = 0.0f, CP_Color rectColor = { 100,100,100,255 });
	//dynamic draw text that uses fontsize as its size of textbox
	void drawText(const char* text, float xPos, float yPos);

	//getters
	float getFontSize();
	int getMoneys();
	int getHealth(void);
	int getMaxHealth(void);

	//setters
	void setFontSize(float size);
	void setMoneys(int moneyAmt);
	void setMaxHealth(int max);
	void setHealth(int hp);
	
	//for nextwave button
	void ButtonInit();
	
	void ButtonDraw();

	//for taking damage when the enemy reaches the end
	void takeDamage(int hp);

	//for losing money when buying things
	void loseMoneys(int moneyAmt);
	//for gaining money when killing enemies
	void gainMoneys(int moneyAmt);

	//for drawing health
	void drawHeart(float x,float y);
	//for drawing currency
	void drawMoneys(float x,float y);

	//for drawing the heart with heartbeats
	int heartOpacity = 155;
	float heartBeatStart = 0.25f;
	float heartBeatTimer = heartBeatStart;
	float heartBeatScale = 1.0f;
	float startOfTimer = 1.75f;
	float timer = startOfTimer;
	
	//images for UI
	CP_Image healthImage = CP_Image_Load("./Assets/UI/full_heart.png");
	CP_Image emptyHeartImage = CP_Image_Load("./Assets/UI/empty_heart.png");
	CP_Image moneysImage = CP_Image_Load("./Assets/UI/money.png");
	CP_Image howToPlayImages[HOW_TO_PLAY_SIZE];

	//currently selected UI element
	currSelected currSelect = currSelected::NONE_TOWER;

	//UI elements
	Tower fireTowerUI;
	Tower iceTowerUI;
	Tower windTowerUI;
	Tower lightningTowerUI;
	Tower levelUpUI;
	Tower mergeUI;
	Tower sellingUI;

	//for drag n drops
	bool grabbingTower = false;

	BaseTower* currentTower = nullptr;
	//array for ALL ui elements
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



