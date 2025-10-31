#include "Game.h"
#include "cprocessing.h"
#include <iostream>
#include <string>
#include <vector>

#include "../../System/Map.h"

#include "../../Enemies/BasicEnemy.h"
#include "../../Enemies/TankEnemy.h"
#include "../../Enemies/SpeedsterEnemy.h"

#include "../../Towers/FireTower.h"
#include "../../Towers/IceTower.h"
#include "../../Towers/LightningTower.h"
#include "../../Towers/WindTower.h"

#include "../../Projectiles/BaseProjectile.h"
#include "../../Utils/Utils.h"

/*!
@file       Game.cpp
@author     Chew Zavier(c.zavier)
@brief      This file contains the definitions of functions to draw the game.
*//*_______________________________________________________________________*/

CP_Font font;

const char* FILE_PATH = "./Assets/Fonts/KenneyFonts/Kenney Mini.ttf";

Map* gameMap;
CP_Vector mapSize;

std::vector<BaseEnemy*> enemiesList;
std::vector<BaseTower*> towerList;
std::vector<BaseProjectile*> projectileList;


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

void Game::drawMoneys(float x, float y)
{
	std::string money = "Money: " + std::to_string(game.getMoneys());
	game.drawText(money.c_str(), x, y);
	CP_Image_Draw(game.moneysImage, x, y, 16 * imageScaling, 16 * imageScaling, 255);
}

void Game::drawHeart(float x, float y)
{
	switch (game.getHealth())
	{
	case(3):
		startOfTimer = 1.75f;
		break;
	case(2):
		startOfTimer = 1.0f;
		break;
	case(1):
		startOfTimer = 0.50f;
		break;
	default:
		startOfTimer = 1.75f;
		break;
	}
	
	if (timer > 0)
	{
		timer += -1 * CP_System_GetDt();
	}
	else
	{
		heartBeatTimer += -1 * CP_System_GetDt();
		if (heartBeatTimer > 0)
		{
			heartOpacity = 255;
			heartBeatScale = 1.25f;
		}
		else
		{
			heartOpacity = 155;
			heartBeatTimer = heartBeatStart;
			timer = startOfTimer;
			heartBeatScale = 1.0f;
		}
	}

	
	double heartSize = (double)game.getHealth() / (double)game.getMaxHealth() * heartBeatScale;
	CP_Image_Draw(game.emptyHeartImage, x, y, CP_Image_GetWidth(game.healthImage) * imageScaling, CP_Image_GetHeight(game.healthImage) * imageScaling, 255);
	CP_Image_Draw(game.healthImage, x, y, CP_Image_GetWidth(game.healthImage) * imageScaling * heartSize,CP_Image_GetHeight(game.healthImage) * imageScaling *heartSize,255);
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

CP_Vector Game::getSpawnLocation()
{
	return spawnLocation;
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
	gameMap->createPath(game.getSpawnLocation(), game.getSpawnLocation());

	game.healthImage = CP_Image_Load("./Assets/UI/full_heart.png");
	game.emptyHeartImage = CP_Image_Load("./Assets/UI/empty_heart.png");
	game.moneysImage = CP_Image_Load("./Assets/UI/money.png");

	game.fireTowerUI.image = CP_Image_Load("./Assets/Towers/fireTower.png");
	game.fireTowerUI.pos = CP_Vector_Set(1500, 200);
	game.fireTowerUI.selection = FIRETOWER;
	game.fireTowerUI.towerCost = 100;

	game.windTowerUI.image = CP_Image_Load("./Assets/Towers/windTower.png");
	game.windTowerUI.pos = CP_Vector_Add(game.fireTowerUI.pos,CP_Vector_Set(0,100));
	game.windTowerUI.selection = WINDTOWER;
	game.windTowerUI.towerCost = 101;

	game.iceTowerUI.image = CP_Image_Load("./Assets/Towers/iceTower.png");
	game.iceTowerUI.pos = CP_Vector_Add(game.windTowerUI.pos, CP_Vector_Set(0, 100));
	game.iceTowerUI.selection = ICETOWER;
	game.iceTowerUI.towerCost = 102;

	game.lightningTowerUI.image = CP_Image_Load("./Assets/Towers/lightningTower.png");
	game.lightningTowerUI.pos = CP_Vector_Add(game.iceTowerUI.pos, CP_Vector_Set(0, 100));
	game.lightningTowerUI.selection = LIGHTNINGTOWER;
	game.lightningTowerUI.towerCost = 103;

	game.uiElements[0] = game.fireTowerUI;
	game.uiElements[1] = game.windTowerUI;
	game.uiElements[2] = game.iceTowerUI;
	game.uiElements[3] = game.lightningTowerUI;
	CP_Settings_TextSize(game.getFontSize());

	//CP_Font_DrawText("YIBBBEEE", 10, 10);
}

void gameUpdate(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(132, 198, 105, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	gameMap->renderMap();
	
	for (int i = 0; i < (sizeof(game.uiElements) / sizeof(game.uiElements[0])); i++)
	{
		CP_Image_Draw(game.uiElements[i].image, game.uiElements[i].pos.x, game.uiElements[i].pos.y, game.uiElements[i].size, game.uiElements[i].size, game.uiElements[i].opacity);
	}
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		for (int i = 0; i < sizeof(game.uiElements) / sizeof(game.uiElements[0]);i++)
		{
			if ((CP_Input_GetMouseX() >= game.uiElements[i].pos.x - game.uiElements[i].radius && CP_Input_GetMouseX() <= game.uiElements[i].pos.x + game.uiElements[i].radius) && (CP_Input_GetMouseY() >= game.uiElements[i].pos.y - game.uiElements[i].radius && CP_Input_GetMouseY() <= game.uiElements[i].pos.y + game.uiElements[i].radius)
				&& game.getMoneys() >= game.uiElements[i].towerCost
				)
			{
				game.currSelect = game.uiElements[i].selection;
				game.uiElements[i].opacity = 100;
			}

		}
	}
	else if (CP_Input_MouseReleased(MOUSE_BUTTON_1) && game.currSelect != NONE_TOWER)
	{
		for (int i = 0; i < sizeof(game.uiElements) / sizeof(game.uiElements[0]); i++)
		{
			game.uiElements[i].opacity = 255;
		}
		if ((CP_Input_GetMouseX() >= 0 && CP_Input_GetMouseX() <= gameMap->getTileSize() * mapSize.x)
			&& (CP_Input_GetMouseY() >= 0 && CP_Input_GetMouseY() <= gameMap->getTileSize() * mapSize.y))
		{
			if (gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).tileType >= TILE_TYPE::GROUND
				&& gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).tileType <= TILE_TYPE::GRASS)
			{
				CP_Vector tempPos = gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).pos;
				bool notOverlapping = true;
				printf("%d", game.currSelect);
				if (towerList.empty())
				{
					switch (game.currSelect)
					{
						case FIRETOWER:
						{
							towerList.push_back(new FireTower(tempPos));
							break;
						}
						case WINDTOWER:
						{
							towerList.push_back(new WindTower(tempPos));
							break;
						}
						case ICETOWER:
						{
							towerList.push_back(new IceTower(tempPos));
							break;
						}
						case LIGHTNINGTOWER:
						{
							towerList.push_back(new LightningTower(tempPos));
							break;
						}
					}
					for (int i = 0; i < sizeof(game.uiElements) / sizeof(game.uiElements[0]); i++)
					{
						if (game.currSelect == game.uiElements[i].selection)
						{
							game.loseMoneys(game.uiElements[i].towerCost);
							break;
						}
					}
					game.currSelect = NONE_TOWER;
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
						switch (game.currSelect)
						{
						case FIRETOWER:
							towerList.push_back(new FireTower(tempPos));
							break;
						case ICETOWER:
							towerList.push_back(new IceTower(tempPos));
							break;
						case WINDTOWER:
							towerList.push_back(new WindTower(tempPos));
							break;
						case LIGHTNINGTOWER:
							towerList.push_back(new LightningTower(tempPos));
							break;
						}
						for (int i = 0; i < sizeof(game.uiElements) / sizeof(game.uiElements[0]); i++)
						{
							if (game.currSelect == game.uiElements[i].selection)
							{
								game.loseMoneys(game.uiElements[i].towerCost);
								break;
							}
						}
						game.currSelect = NONE_TOWER;
					}
				}

			}
		}
	}
	if (CP_Input_MouseDown(MOUSE_BUTTON_1) && game.currSelect != currSelected::NONE_TOWER)
	{
		switch (game.currSelect)
		{
		case FIRETOWER:
			CP_Image_Draw(game.fireTowerUI.image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50,50, 155);
			break;
		case WINDTOWER:
			CP_Image_Draw(game.windTowerUI.image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50, 155);
			break;
		case ICETOWER:
			CP_Image_Draw(game.iceTowerUI.image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50, 155);
			break;
		case LIGHTNINGTOWER:
			CP_Image_Draw(game.lightningTowerUI.image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50, 155);
			break;
		}
	}
	game.drawHeart(CP_System_GetWindowWidth() / 2.0f, 100.0f);
	game.drawMoneys(CP_System_GetWindowWidth() / 2.0f, 300.0f);
	if (CP_Input_KeyReleased(KEY_H))
	{
		game.takeDamage(1);
	}
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_2))
	{
		game.gainMoneys(100);
	}

	if (CP_Input_KeyReleased(KEY_1))
		enemiesList.push_back(new BasicEnemy(game.getSpawnLocation()));
	if (CP_Input_KeyReleased(KEY_2))
		enemiesList.push_back(new TankEnemy(game.getSpawnLocation()));
	if (CP_Input_KeyReleased(KEY_3))
		enemiesList.push_back(new SpeedsterEnemy(game.getSpawnLocation()));
	//if (CP_Input_KeyReleased(KEY_4))
	//{
	//	for (BaseEnemy* enemy : enemiesList)
	//		enemy->SetHealth(enemy->GetHealth() - 1);
	//}

	// enemy movement
	for (int i = 0; i < enemiesList.size(); ++i)
	{
		BaseEnemy* enemy = enemiesList[i];

		if (gameMap->getTile(enemy->GetLocation().x, enemy->GetLocation().y).tileType == TILE_TYPE::ENDPOINT)
		{
			game.takeDamage(1);
			enemiesList.erase(enemiesList.begin() + i--);
			delete enemy;
		}
		else if (enemy->GetHealth() <= 0)
		{
			game.gainMoneys(100);
			enemiesList.erase(enemiesList.begin() + i--);
			delete enemy;
		}
		else
		{
			enemy->Move(gameMap);
			enemy->Render();
		}
	}

	// render and update towers, check for nearby enemies and target them
	if (towerList.size())
	{
		for (BaseTower* tower : towerList)
		{
			tower->Update();
			tower->Render();

			for (BaseEnemy* enemy : enemiesList)
			{
				float dist = CP_Vector_Distance(tower->getPosition(), enemy->GetLocation());
				//if (dist <= tower->getDetectionDistance() && tower->getCooldownTime() <= 0.f)
				if(areCirclesIntersecting(tower->getPosition(),tower->getDetectionDistance(),enemy->GetLocation(),enemy->GetSpriteSize()/2.0f) && tower->getCooldownTime() <= 0.f)
				{
					CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - tower->getPosition().x, enemy->GetLocation().y - tower->getPosition().y));
					projectileList.push_back(tower->Attack(direction));
				}
			}
		}
	}

	// projectile collision
	for (int i = 0; i < projectileList.size(); i++)
	{
		projectileList[i]->Update();
		projectileList[i]->Render();

		if (projectileList[i]->GetLifespan() <= 0.f ||
			(projectileList[i]->GetLocation().x >= gameMap->getTileSize() * mapSize.x ||
				projectileList[i]->GetLocation().y >= gameMap->getTileSize() * mapSize.y))
		{
			BaseProjectile* proj = projectileList[i];
			projectileList.erase(projectileList.begin() + i);
			delete proj;
		}
		else
		{
			for (int j = 0; j < enemiesList.size(); j++)
			{
				BaseEnemy* enemy = enemiesList[j];
				if (areCirclesIntersecting(projectileList[i]->GetLocation(), projectileList[i]->GetRadius(), enemy->GetLocation(), enemy->GetSpriteSize()/2.0f))
				{
					enemy->SetHealth(enemy->GetHealth() - 1);

					BaseProjectile* proj = projectileList[i];
					projectileList.erase(projectileList.begin() + i);
					delete proj;

					break;
				}
				
			}
		}

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

