#include "Game.h"
#include "cprocessing.h"
#include <iostream>
#include <string>
#include <vector>
#include "Game.h"
#include "../../System/Map.h"
#include "../../Enemies/BasicEnemy.h"
#include "../../Enemies/TankEnemy.h"
#include "../../Enemies/SpeedsterEnemy.h"
#include "../../Towers/FireTower.h"

/*!
@file       Game.cpp
@author     Chew Zavier(c.zavier)
@brief      This file contains the definitions of functions to draw the Graphical User Interface (game).
*//*_______________________________________________________________________*/

CP_Font font;

const char* FILE_PATH = "./Assets/Fonts/KenneyFonts/Kenney Mini.ttf";

Map* gameMap;
CP_Vector mapSize;

std::vector<BaseEnemy*> enemiesList;
std::vector<BaseTower*> towerList;

Game game;
void Game::drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle, float cornerRadius, CP_Color rectColor)
{
	CP_Settings_Fill(CP_Color_Create(255,255,255,255));
	CP_Graphics_DrawRectAdvanced(posX, posY, rectWidth, rectHeight, angle,cornerRadius);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
}

void Game::drawText(const char* text, float xPos,float yPos)
{
	CP_Font_DrawTextBox(text, xPos, yPos, sizeof(text) * fontSize);
}

void Game::setFontSize(float size)
{
	fontSize = size;
}

float Game::getFontSize()
{
	return fontSize;
}
int Game::getMoneys()
{
	return moneys;
}
void Game::setMoneys(int moneyAmt)
{
	moneys = moneyAmt;
}
void Game::loseMoneys(int moneyAmt)
{
	game.setMoneys(getMoneys() - moneyAmt);
}
void Game::gainMoneys(int moneyAmt)
{
	game.setMoneys(getMoneys() + moneyAmt);
}

void Game::drawHeart(float x, float y)
{
	CP_Image_Draw(game.emptyHeartImage, x, y, CP_Image_GetWidth(game.emptyHeartImage) * imageScaling, CP_Image_GetHeight(game.emptyHeartImage) * imageScaling, 155);
	double heartSize = (double)game.getHealth() / (double)game.getMaxHealth();
	CP_Image_Draw(game.healthImage, x, y, CP_Image_GetWidth(game.healthImage) * imageScaling * heartSize,CP_Image_GetHeight(game.healthImage) * imageScaling *heartSize,255);
	std::string health = "Health: " + std::to_string(game.getHealth());
	game.drawText(health.c_str(), CP_System_GetWindowWidth() / 2, 100);
}

int Game::getHealth()
{
	return health;
}
int Game::getMaxHealth()
{
	return maxHealth;
}
void Game::setMaxHealth(int max)
{
	maxHealth = max;
}
void Game::setHealth(int hp)
{
	health = hp;
}
void Game::takeDamage(int hp)
{
	health -= hp;
	//CP_Image_Draw(game.healthImage, CP_System_GetWindowWidth() / 2.0, 100, 128, 128, 255);
	health = CP_Math_ClampInt(health, 0, game.getMaxHealth());
}

void gameInit(void)
{	
	font = CP_Font_Load(FILE_PATH);
	if (!CP_Font_Load(FILE_PATH))
	{
		throw "File path invalid, please double check.";
	}
	CP_Font_Set(font);
	game.setFontSize(20);
	CP_Settings_TextSize(game.getFontSize());

	gameMap = Map::GetInstance();
	gameMap->loadMap("Map2");

	mapSize = gameMap->getDimensions();

	game.healthImage = CP_Image_Load("./Assets/pixelplatformer/UI/full_heart.png");
	game.emptyHeartImage = CP_Image_Load("./Assets/pixelplatformer/UI/empty_heart.png");
	game.fireTowerImage = CP_Image_Load("./Assets/kenney_tiny-battle/Tiles/tile_0068.png");
	CP_Settings_TextSize(game.getFontSize());

	//CP_Font_DrawText("YIBBBEEE", 10, 10);
}

void gameUpdate(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(132, 198, 105, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	gameMap->renderMap();

	game.drawHeart(CP_System_GetWindowWidth() / 2.0f, 100.0f);

	if (CP_Input_KeyReleased(KEY_H))
	{
		game.takeDamage(1);
	}
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_2))
	{
		game.gainMoneys(100);
	}

	if (CP_Input_KeyReleased(KEY_1))
		enemiesList.push_back(new BasicEnemy(CP_Vector_Set(24.0f, 24.0f)));
	if (CP_Input_KeyReleased(KEY_2))
		enemiesList.push_back(new TankEnemy(CP_Vector_Set(24.0f, 24.0f)));
	if (CP_Input_KeyReleased(KEY_3))
		enemiesList.push_back(new SpeedsterEnemy(CP_Vector_Set(24.0f, 24.0f)));

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && (CP_Input_GetMouseX() >= 0 && CP_Input_GetMouseX() <= gameMap->getTileSize() * mapSize.x)
								&& (CP_Input_GetMouseY() >= 0 && CP_Input_GetMouseY() <= gameMap->getTileSize() * mapSize.y))
	{
		if (gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).tileType >= TILE_TYPE::GROUND
			&& gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).tileType <= TILE_TYPE::GRASS)
		{
			CP_Vector tempPos = gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).pos;
			bool notOverlapping = true;

			if (towerList.empty())
			{
				towerList.push_back(new FireTower(tempPos));
				std::cout << "spawn 1st item" << std::endl;
			}
			else
			{
				for (BaseTower* tower : towerList)
				{
					float distance = CP_Vector_Distance(tower->getPosition(), tempPos);
					if (distance == 0)
					{
						notOverlapping = false;
					}
				}

				if (notOverlapping)
				{
					towerList.push_back(new FireTower(tempPos));
					std::cout << "spawn" << std::endl;
				}
			}
			
		}
	}

	for (BaseEnemy* enemy : enemiesList)
	{
		enemy->Move();
		enemy->Render();
	}


	for (BaseTower* tower : towerList)
	{
		tower->Render();
	}
	
	if (CP_Input_MouseDragged(MOUSE_BUTTON_1))
	{

	}

	CP_Image_Draw(game.fireTowerImage, 1500, 200, 96, 96, 255);
	
	std::string money = "Money: " + std::to_string(game.getMoneys());
	game.drawText(money.c_str(), CP_System_GetWindowWidth()/2.0, 300);
}

void gameExit(void)
{
	CP_Font_Free(font);
	gameMap->resetMap(true);
	for (BaseEnemy* enemy : enemiesList)
	{
		delete enemy;
	}
}

void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle, float cornerRadius, CP_Color rectColor)
{
	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRectAdvanced(posX, posY, rectWidth, rectHeight, angle,cornerRadius);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
}

void drawText(const char* text, float xPos,float yPos)
{
	CP_Font_DrawTextBox(text, xPos, yPos, sizeof(text) * game.getFontSize());
		game.takeDamage(1);
	
	if (CP_Input_KeyDown(KEY_F))
	{
		game.setFontSize(game.getFontSize() + 1);
		CP_Settings_TextSize(game.getFontSize());
	}
	else if (CP_Input_KeyDown(KEY_G))
	{
		game.setFontSize(game.getFontSize() - 1);
		CP_Settings_TextSize(game.getFontSize());
	}
	//drawText("hoorah",CP_Input_GetMouseX(), CP_Input_GetMouseY());
}

