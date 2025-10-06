//#include "Game.h"
#include "cprocessing.h"
#include <iostream>
#include <string>
#include <vector>
#include "Game.h"
#include "../../System/Map.h"
#include "../../Enemies/BasicEnemy.h"
#include "../../Towers/FireTower.h"

/*!
@file       Game.cpp
@author     Chew Zavier(c.zavier)
@brief      This file contains the definitions of functions to draw the Graphical User Interface (game).
*//*_______________________________________________________________________*/

CP_Font font;
int health = 10;
const char* FILE_PATH = "./Assets/Fonts/KenneyFonts/Kenney Mini.ttf";
float fontSize = 12.0f;

Map* gameMap;
CP_Vector mapSize;

std::vector<BaseEnemy*> enemiesList;
std::vector<BaseTower*> towerList;

void gameInit(void)
{	
	font = CP_Font_Load(FILE_PATH);
	if (!CP_Font_Load(FILE_PATH))
	{
		throw "File path invalid, please double check.";
	}
	CP_Font_Set(font);

	CP_Settings_TextSize(fontSize);

	gameMap = Map::GetInstance();
	gameMap->loadMap("Map2");

	mapSize = gameMap->getDimensions();
	//CP_Font_DrawText("YIBBBEEE", 10, 10);
}

void gameUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(132, 198, 105, 255));
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		health--;
		drawText("Health" + health, 100, 100);
	}
	//drawText("hoorah",CP_Input_GetMouseX(), CP_Input_GetMouseY());

	gameMap->renderMap();

	if (CP_Input_KeyReleased(KEY_SPACE))
	{
		enemiesList.push_back(new BasicEnemy(CP_Vector_Set(24.0f, 24.0f)));
	}

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
	CP_Settings_Fill(CP_Color_Create(255,255,255,255));
	CP_Graphics_DrawRectAdvanced(posX, posY, rectWidth, rectHeight, angle,cornerRadius);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
}

void drawText(const char* text, float xPos,float yPos)
{
	CP_Font_DrawTextBox(text, xPos, yPos, sizeof(text) * fontSize);
}

void setFontSize(float size)
{
	fontSize = size;
}

float getFontSize()
{
	return fontSize;
}
