#include "Game.h"
#include "cprocessing.h"
#include <iostream>
#include <string>
#include <vector>

#include "../../System/Map.h"
#include "../../System/SoundManager.h"

#include "../../Enemies/BasicEnemy.h"
#include "../../Enemies/TankEnemy.h"
#include "../../Enemies/SpeedsterEnemy.h"
#include "../../Enemies/BossEnemy.h"

#include "../../Towers/FireTower.h"
#include "../../Towers/IceTower.h"
#include "../../Towers/LightningTower.h"
#include "../../Towers/WindTower.h"

#include "../../Towers/LavaTower.h"
#include "../../Towers/FrostTower.h"

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
	CP_Image_Draw(game.moneysImage, x, y, 16 * imageScaling, 16 * imageScaling, 255);
	game.drawText(money.c_str(), x, y);
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
	gameMap->loadMap("Edit2");

	mapSize = gameMap->getDimensions();

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

	game.levelUpUI.image = CP_Image_Load("./Assets/UI/levelup.png");
	game.levelUpUI.pos = CP_Vector_Set(1500, 800);
	game.levelUpUI.towerCost = 0;

	game.uiElements[0] = game.fireTowerUI;
	game.uiElements[1] = game.windTowerUI;
	game.uiElements[2] = game.iceTowerUI;
	game.uiElements[3] = game.lightningTowerUI;
	game.uiElements[4] = game.levelUpUI;
	CP_Settings_TextSize(game.getFontSize());

	

	game.waveManager = new WaveManager(gameMap->getSpawnpoint());

	game.currentTower = new BaseTower();
	//CP_Font_DrawText("YIBBBEEE", 10, 10);

	SoundManager::GetInstance()->playBGM(GAME_00_BGM);
	SoundManager::GetInstance()->queueNextBGM(GAME_01_BGM);
}

void gameUpdate(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(132, 198, 105, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	SoundManager::GetInstance()->Update();
	gameMap->renderMap();

	for (int i = 0; i < (sizeof(game.uiElements) / sizeof(game.uiElements[0])); i++)
	{
		if (game.getMoneys() < game.uiElements[i].towerCost)
		{
			game.uiElements[i].opacity = 100;
		}
		else
			game.uiElements[i].opacity = 255;
		CP_Image_Draw(game.uiElements[i].image, game.uiElements[i].pos.x, game.uiElements[i].pos.y, game.uiElements[i].size, game.uiElements[i].size, game.uiElements[i].opacity);
	}
	// MOUSE CLICKED
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		for (int i = 0; i < sizeof(game.uiElements) / sizeof(game.uiElements[0]); i++)
		{
			if( (isAreaClicked(game.uiElements[i].pos,game.uiElements[i].size,game.uiElements[i].size,CP_Vector_Set(CP_Input_GetMouseX(),CP_Input_GetMouseY()))) && game.getMoneys() >= game.uiElements[i].towerCost)
			{
				game.currSelect = game.uiElements[i].selection;
				game.uiElements[i].opacity = 100;
			}

		}
	}
	
	// MOUSE DOWN
	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		switch (game.currSelect)
		{
		case FIRETOWER:
			CP_Image_Draw(game.fireTowerUI.image, CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50, 155);
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
		default:
			break;
		}

		// render "ghost" tower for dragging existing towers
		if ((CP_Input_GetMouseX() >= 0 && CP_Input_GetMouseX() <= gameMap->getTileSize() * mapSize.x)
			&& (CP_Input_GetMouseY() >= 0 && CP_Input_GetMouseY() <= gameMap->getTileSize() * mapSize.y))
		{
			// unholy fuck ahh code that should not exist
			for (BaseTower* tower : towerList)
			{
				float dist = CP_Vector_Distance(tower->getPosition(), CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY()));
				if (dist <= 24.f && !game.grabbingTower)
				{
					if (tower->getTowerType() == TOWER_TYPE::FIRETOWER
						|| tower->getTowerType() == TOWER_TYPE::ICETOWER
						|| tower->getTowerType() == TOWER_TYPE::LIGHTNINGTOWER
						|| tower->getTowerType() == TOWER_TYPE::WINDTOWER)
					{
						game.currentTower = tower;
						game.grabbingTower = true;
					}
				}
			}

			if (game.currentTower->getImage() != NULL && game.grabbingTower)
				CP_Image_Draw(game.currentTower->getImage(), CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50, 155);
		}
	}
	
	// MOUSE RELEASED
	if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
	{
		if (game.currSelect != NONE_TOWER && game.currSelect != LEVELUP)
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
						SoundManager::GetInstance()->playSFX(TOWER_PLACE_SFX);
					}
					else
					{
						int mergeId;
						for (int i = 0; i < towerList.size(); ++i)
						{
							BaseTower* tower = towerList[i];
							float distance = CP_Vector_Distance(tower->getPosition(), tempPos);
							if (distance == 0)
							{
								notOverlapping = false;
								mergeId = i;
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
							SoundManager::GetInstance()->playSFX(TOWER_PLACE_SFX);
						}
						else
						{
							// Merging
							BaseTower* toDelete = towerList[mergeId];
							towerList.erase(towerList.begin() + mergeId);
							//delete toDelete;
							toDelete = nullptr;

							switch (game.currSelect)
							{
							case FIRETOWER:
								towerList.push_back(new LavaTower(tempPos));
								break;
							case ICETOWER:
								towerList.push_back(new FrostTower(tempPos));
								break;
							case LIGHTNINGTOWER:
								towerList.push_back(new LightningTower(tempPos)); // REPLACE WITH STORMTOWER WHEN TOWER CLASS IS MADE
								break;
							case WINDTOWER:
								towerList.push_back(new WindTower(tempPos)); // REPLACE WITH HURRICANETOWER WHEN TOWER CLASS IS MADE
								break;
							}

							SoundManager::GetInstance()->playSFX(TOWER_MERGE_SFX);
						}
					}
				}
			}
		}
		else if (game.grabbingTower && game.currentTower)
		{
			int targetId = -1;

			CP_Vector tempPos = gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).pos;

			for (int i = 0; i < towerList.size(); i++)
			{
				BaseTower* tower = towerList[i];

				if (tower == game.currentTower)
					continue;

				float distance = CP_Vector_Distance(tower->getPosition(), tempPos);
				if (distance <= 24.f)
				{
					targetId = i;
					break;
				}
			}

					// delete both towers, spawn fused tower where mergeId2 is
			if (targetId != -1)
			{
				BaseTower* dragged = game.currentTower;
				BaseTower* target = towerList[targetId];

				if (dragged->getTowerType() == target->getTowerType())
				{
					CP_Vector mergedPos = target->getPosition();
					TOWER_TYPE type = target->getTowerType();

					switch (type)
					{
					case TOWER_TYPE::FIRETOWER:
						towerList.push_back(new LavaTower(mergedPos));
						break;
					case TOWER_TYPE::ICETOWER:
						towerList.push_back(new FrostTower(mergedPos));
						break;
					case TOWER_TYPE::LIGHTNINGTOWER:
						towerList.push_back(new LightningTower(mergedPos)); // REPLACE WITH STORMTOWER WHEN TOWER CLASS IS MADE
						break;
					case TOWER_TYPE::WINDTOWER:
						towerList.push_back(new WindTower(mergedPos)); // REPLACE WITH HURRICANETOWER WHEN TOWER CLASS IS MADE
						break;
					}

					// Erase both current and target towers zzzzzzzz
					for (int i = towerList.size() - 1; i >= 0; --i)
					{
						if (towerList[i] == dragged || towerList[i] == target)
						{
							towerList[i] = nullptr;
							towerList.erase(towerList.begin() + i);
						}
					}


				}
			}
			game.grabbingTower = false;
			//game.currentTower->setImage(NULL);
		}
	}

	game.drawHeart(1500, 700.0f);
	game.drawMoneys(1350, 100.0f);

	if (CP_Input_KeyReleased(KEY_H))
	{
		game.takeDamage(1);
	}
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_2))
	{
		game.gainMoneys(100);
	}

	game.waveManager->Update(&enemiesList);

	if (CP_Input_KeyReleased(KEY_SPACE))
	{
		CP_Vector dir = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (towerList.size())
		{
			for (BaseTower* tower : towerList)
			{
				tower->Update();
				tower->Render();
				projectileList.push_back(new BaseProjectile(tower->getPosition(),dir,tower->getDamage(),tower->getSpeed(), tower->getColor()));
			}
		}
	}
	if (CP_Input_KeyReleased(KEY_1))
		enemiesList.push_back(new BasicEnemy(gameMap->getSpawnpoint()));
	if (CP_Input_KeyReleased(KEY_2))
		enemiesList.push_back(new TankEnemy(gameMap->getSpawnpoint()));
	if (CP_Input_KeyReleased(KEY_3))
		enemiesList.push_back(new SpeedsterEnemy(gameMap->getSpawnpoint()));
	if (CP_Input_KeyReleased(KEY_4))
		enemiesList.push_back(new BossEnemy(gameMap->getSpawnpoint()));
	if (CP_Input_KeyReleased(KEY_SPACE))
		game.waveManager->SpawnWave(gameMap->getSpawnpoint());


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
			game.gainMoneys(enemy->GetReward());
			enemiesList.erase(enemiesList.begin() + i--);

			switch (enemy->GetEnemyType())
			{
			case EnemyType::BASIC:
				SoundManager::GetInstance()->playSFX(ENEMY_BASIC_DEATH_SFX);
				break;
			case EnemyType::SPEEDSTER:
				SoundManager::GetInstance()->playSFX(ENEMY_SPEEDSTER_DEATH_SFX);
				break;
			case EnemyType::TANK:
				SoundManager::GetInstance()->playSFX(ENEMY_TANK_DEATH_SFX);
				break;
			}
			delete enemy;
		}
		else
		{
			enemy->Move(gameMap);
			enemy->Render();
		}

	}


	// render and update towers, check for nearby enemies and target them
	for (BaseTower* tower : towerList)
	{
		tower->Update();
		tower->Render();

		bool bossNearby = false;

		for (BaseEnemy* enemy : enemiesList)
		{

			if (areCirclesIntersecting(tower->getPosition(), tower->getDetectionDistance(),
				enemy->GetLocation(), enemy->GetSpriteSize() / 2.0f) &&
				tower->getCooldownTime() <= 0.f)
			{
				projectileList.push_back(tower->Attack(enemy));
			}

			// Check if a boss is nearby
			if (BossEnemy* boss = dynamic_cast<BossEnemy*>(enemy))
			{
				float distance = CP_Vector_Distance(tower->getPosition(), boss->GetLocation());
				if (distance < 100.0f) // matches the aura radius exactly
				{
					bossNearby = true;
				}
			}
		}

		// Apply or reset slowdown
		if (bossNearby != tower->slowed)
		{
			if (bossNearby)
			{
				printf("Boss entered range, slowing tower\n");
				tower->ApplySlowdown(5.0f);
			}
			else
			{
				printf("Boss left range, resetting cooldown\n");
				tower->ResetCooldown();
			}
			tower->slowed = bossNearby;
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
			//delete proj;
		}
		else
		{
			for (int j = 0; j < enemiesList.size(); j++)
			{
				BaseEnemy* enemy = enemiesList[j];
				if (areCirclesIntersecting(projectileList[i]->GetLocation(), projectileList[i]->GetRadius(), enemy->GetLocation(), enemy->GetSpriteSize()/2.0f))
				{
					//enemy->SetHealth(enemy->GetHealth() - projectileList[i]->getProjectileDamage());
					if (projectileList[i]->getProjType() == PROJECTILE_TYPE::CHAIN)
					{
						projectileList[i]->chainHit(enemiesList,enemy);	
					}
					else
						projectileList[i]->onHit(enemy);

					BaseProjectile* proj = projectileList[i];
					projectileList.erase(projectileList.begin() + i);
					//delete proj;

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

	delete game.waveManager;
	SoundManager::GetInstance()->stopBGM();
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

