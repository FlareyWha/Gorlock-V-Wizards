	#include "Game.h"
	#include "cprocessing.h"
	#include <iostream>
	#include <string>
	#include <vector>

	#include "../../System/Map.h"
	#include "../../System/SoundManager.h"
	#include "../../System/SceneManager.h"

	#include "../../scenes/PauseMenu/PauseMenu.h"

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
	#include "../../Towers/StormTower.h"
	#include "../../Towers/HurricaneTower.h"

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

		Game game;

		std::vector<BaseEnemy*> enemiesList;
		std::vector<BaseTower*> towerList;
		std::vector<BaseProjectile*> projectileList;



		void Game::drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle, float cornerRadius, CP_Color rectColor)
		{
			CP_Settings_Fill(rectColor);
			CP_Graphics_DrawRectAdvanced(posX, posY, rectWidth, rectHeight, angle,cornerRadius);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		}


		void Game::drawText(const char* text, float xPos,float yPos)
		{
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
			CP_Font_DrawTextBox(text, xPos, yPos, sizeof(text) * game.getFontSize());
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
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
			std::string money = ": " + std::to_string(game.getMoneys());
			CP_Image_Draw(game.moneysImage, x, y, 16 * imageScaling, 16 * imageScaling, 255);
			CP_Settings_TextSize(35.f);
			game.drawText(money.c_str(), x+60, y);
			CP_Settings_TextSize(20.f);
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

			if (health <= 0 && !game.shouldShowLosescreen())
			{
				game.setLose(true);
				SoundManager::GetInstance()->playSFX(GAME_LOSE_SFX);
				SoundManager::GetInstance()->stopBGM();
			}
		}

		bool Game::shouldShowWinscreen(void)
		{
			return winScreen;
		}

		bool Game::shouldShowLosescreen(void)
		{
			return loseScreen;
		}

		void Game::setWin(bool win)
		{
			winScreen = win;
		}

		void Game::setLose(bool lose)
		{
			loseScreen = lose;
		}

		void Game::ButtonInit()
		{
			nextWave = new Button(1380, 850, 130, 50, "Next Wave");
			back = new Button(CP_System_GetWindowWidth() * 0.5f, CP_System_GetWindowHeight() * 0.5f, 260, 100, "Back");
		}

		void Game::ButtonDraw()
		{
			nextWave->Draw();
		}

		void Game::CleanUpGame() {
			// Delete all enemies
			for (BaseEnemy* enemy : enemiesList) {
				delete enemy;
			}
			enemiesList.clear();

			// Delete all towers
			for (BaseTower* tower : towerList) {
				delete tower;
			}
			towerList.clear();

			// Delete all projectiles
			for (BaseProjectile* proj : projectileList) {
				delete proj;
			}
			projectileList.clear();

			// Delete wave manager
			if (waveManager) {
				delete waveManager;
				waveManager = nullptr;
			}

			// Reset map
			if (gameMap) {
				gameMap->resetMap(true);
			}

			// Reset player stats
			health = maxHealth;
			moneys = 0;
			currSelect = NONE_TOWER;
			grabbingTower = false;
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

			game.ButtonInit();

			gameMap = Map::GetInstance();
			gameMap->loadMap("NewMap");

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
			game.windTowerUI.towerCost = 150;

			game.iceTowerUI.image = CP_Image_Load("./Assets/Towers/iceTower.png");
			game.iceTowerUI.pos = CP_Vector_Add(game.windTowerUI.pos, CP_Vector_Set(0, 100));
			game.iceTowerUI.selection = ICETOWER;
			game.iceTowerUI.towerCost = 125;

			game.lightningTowerUI.image = CP_Image_Load("./Assets/Towers/lightningTower.png");
			game.lightningTowerUI.pos = CP_Vector_Add(game.iceTowerUI.pos, CP_Vector_Set(0, 100));
			game.lightningTowerUI.selection = LIGHTNINGTOWER;
			game.lightningTowerUI.towerCost = 200;

			game.levelUpUI.image = CP_Image_Load("./Assets/UI/levelup.png");
			game.levelUpUI.pos = CP_Vector_Set(1500, 800);
			game.levelUpUI.selection = LEVELUP;
			game.levelUpUI.towerCost = 0;

			game.uiElements[0] = game.fireTowerUI;
			game.uiElements[1] = game.windTowerUI;
			game.uiElements[2] = game.iceTowerUI;
			game.uiElements[3] = game.lightningTowerUI;
			game.uiElements[4] = game.levelUpUI;
			CP_Settings_TextSize(game.getFontSize());

	

			game.waveManager = new WaveManager(gameMap->getSpawnpoint());

			game.currentTower = new BaseTower();

			SoundManager::GetInstance()->playBGM(GAME_00_BGM);
			SoundManager::GetInstance()->queueNextBGM(GAME_01_BGM);
		}

		void gameUpdate(void)
		{
			CP_Graphics_ClearBackground(CP_Color_Create(132, 198, 105, 255));
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

			SoundManager::GetInstance()->Update();
			gameMap->renderMap();

			if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
				SceneManager::GetInstance()->ChangeScenes(Scenes::PAUSE_MENU_SCENE);
				return;
			}			
									
			game.ButtonDraw();

			for (int i = 0; i < (sizeof(game.uiElements) / sizeof(game.uiElements[0])); i++)
			{
				if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
				{
					if ((isAreaClicked(game.uiElements[i].pos, game.uiElements[i].size, game.uiElements[i].size, CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY()))) && game.getMoneys() >= game.uiElements[i].towerCost)
					{
						if (game.currSelect != game.uiElements[i].selection)
							game.currSelect = game.uiElements[i].selection;
						else
							game.currSelect = NONE_TOWER;
					}
				}
				if (game.getMoneys() < game.uiElements[i].towerCost || game.currSelect == game.uiElements[i].selection)
				{
					game.uiElements[i].opacity = 100;
				}
				else
					game.uiElements[i].opacity = 255;
				CP_Image_Draw(game.uiElements[i].image, game.uiElements[i].pos.x, game.uiElements[i].pos.y, game.uiElements[i].size, game.uiElements[i].size, game.uiElements[i].opacity);
				if (game.uiElements[i].selection != LEVELUP)
				{
					std::string costs = std::to_string(game.uiElements[i].towerCost);
					CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_MIDDLE);
					game.drawText(costs.c_str(), game.uiElements[i].pos.x + 10, game.uiElements[i].pos.y + 35);
					CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
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
						if (dist <= 24.f && !game.grabbingTower && game.currSelect!=LEVELUP)
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

			if (game.currSelect == LEVELUP)
			{
				CP_Image_Draw(CP_Image_Load("./Assets/UI/levelupcursor.png"), CP_Input_GetMouseX() + 25, CP_Input_GetMouseY() - 10, 75, 75, 255);
			}
	
			// MOUSE RELEASED
			if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
			{
				if (game.currSelect != NONE_TOWER && game.currSelect != LEVELUP)
				{
					if ((CP_Input_GetMouseX() >= 0 && CP_Input_GetMouseX() <= gameMap->getTileSize() * mapSize.x)
						&& (CP_Input_GetMouseY() >= 0 && CP_Input_GetMouseY() <= gameMap->getTileSize() * mapSize.y))
					{
						if (gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).tileType >= TILE_TYPE::GROUND
							&& gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).tileType <= TILE_TYPE::GRASS)
						{
							CP_Vector tempPos = gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).pos;
							bool notOverlapping = true;
					
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
								//else
								//{
								//	// Merging
								//	BaseTower* toDelete = towerList[mergeId];
								//	towerList.erase(towerList.begin() + mergeId);
								//	//delete toDelete;
								//	toDelete = nullptr;
								//
								//	switch (game.currSelect)
								//	{
								//	case FIRETOWER:
								//		towerList.push_back(new LavaTower(tempPos));
								//		break;
								//	case ICETOWER:
								//		towerList.push_back(new FrostTower(tempPos));
								//		break;
								//	case LIGHTNINGTOWER:
								//		towerList.push_back(new LightningTower(tempPos)); // REPLACE WITH STORMTOWER WHEN TOWER CLASS IS MADE
								//		break;
								//	case WINDTOWER:
								//		towerList.push_back(new WindTower(tempPos)); // REPLACE WITH HURRICANETOWER WHEN TOWER CLASS IS MADE
								//		break;
								//	}
								//
								//	SoundManager::GetInstance()->playSFX(TOWER_MERGE_SFX);
								//}
							}
						}
					}
					game.currSelect = NONE_TOWER;
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

						if (dragged->getTowerType() == target->getTowerType() && dragged->getLevel() == dragged->getMaxLevel() && target->getLevel() == target->getMaxLevel())
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
								towerList.push_back(new StormTower(mergedPos)); // REPLACE WITH STORMTOWER WHEN TOWER CLASS IS MADE
								break;
							case TOWER_TYPE::WINDTOWER:
								towerList.push_back(new HurricaneTower(mergedPos));
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

				//game.waveManager->SpawnWave(game.getSpawnLocation());
			if (CP_Input_KeyReleased(KEY_1))
				enemiesList.push_back(new BasicEnemy(gameMap->getSpawnpoint()));
			if (CP_Input_KeyReleased(KEY_2))
				enemiesList.push_back(new TankEnemy(gameMap->getSpawnpoint()));
			if (CP_Input_KeyReleased(KEY_3))
				enemiesList.push_back(new SpeedsterEnemy(gameMap->getSpawnpoint()));
			if (CP_Input_KeyReleased(KEY_4))
				enemiesList.push_back(new BossEnemy(gameMap->getSpawnpoint()));
			if (game.nextWave->IsClicked())
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
					case EnemyType::BOSS:
						SoundManager::GetInstance()->playSFX(ENEMY_BOSS_DEATH_1_SFX);
						SoundManager::GetInstance()->playSFX(ENEMY_BOSS_DEATH_2_SFX);
						SoundManager::GetInstance()->playSFX(GAME_WIN_SFX);
						SoundManager::GetInstance()->stopBGM();
						game.setWin(true);
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
				bool bossNearby = false;

				FrostTower* frostTower = dynamic_cast<FrostTower*>(tower);
				if (frostTower && !enemiesList.empty())
				{
					frostTower->TrackEnemy(enemiesList);
					frostTower->Update();

					if (frostTower->getCooldownTime() <= 0.f && frostTower->trackedEnemy)
					{
						projectileList.push_back(frostTower->Attack(frostTower->trackedEnemy));
					}


					// Boss check for FrostTower
					for (BaseEnemy* enemy : enemiesList)
					{
						if (BossEnemy* boss = dynamic_cast<BossEnemy*>(enemy))
						{
							float distance = CP_Vector_Distance(tower->getPosition(), boss->GetLocation());
							if (distance < 100.0f)
							{
								bossNearby = true;
							}
						}
					}
				}
				else
				{
					tower->Update();


					for (BaseEnemy* enemy : enemiesList)
					{

						if (areCirclesIntersecting(tower->getPosition(), tower->getDetectionDistance(),
							enemy->GetLocation(), enemy->GetSpriteSize() / 2.0f) &&
							tower->getCooldownTime() <= 0.f)
						{
							projectileList.push_back(tower->Attack(enemy));
							if (tower->getTowerType() == TOWER_TYPE::HURRICANETOWER || tower->getTowerType() == TOWER_TYPE::LAVATOWER)
							{
								if (tower->getSecondaryCD() <= 0.f)
								{
									projectileList.push_back(tower->SpawnSecondary(enemy));
								}
							}
							break;
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
				}
				tower->Render();

				if (bossNearby != tower->slowed())
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
				}

				//check if my current selected is leveling up
				if (game.currSelect == LEVELUP)
				{
					std::string cost = std::to_string(tower->getUpgradeCosts());
					if (tower->getLevel() != tower->getMaxLevel() && tower->getTowerType() != TOWER_TYPE::HURRICANETOWER
						&& tower->getTowerType() != TOWER_TYPE::LAVATOWER && tower->getTowerType() != TOWER_TYPE::STORMTOWER
						&& tower->getTowerType() != TOWER_TYPE::FROSTTOWER)
					{
							game.drawText(cost.c_str(), tower->getPosition().x, tower->getPosition().y);
					}
					else if (tower->getLevel() == tower->getMaxLevel() || tower->getTowerType() == TOWER_TYPE::HURRICANETOWER
						|| tower->getTowerType() == TOWER_TYPE::LAVATOWER || tower->getTowerType() == TOWER_TYPE::STORMTOWER
						|| tower->getTowerType() == TOWER_TYPE::FROSTTOWER)
					{
						game.drawText("MAX", tower->getPosition().x, tower->getPosition().y);
					}
					if (game.getMoneys() < tower->getUpgradeCosts() || tower->getLevel() == tower->getMaxLevel()
						|| tower->getTowerType() == TOWER_TYPE::HURRICANETOWER || tower->getTowerType() == TOWER_TYPE::LAVATOWER 
						|| tower->getTowerType() == TOWER_TYPE::STORMTOWER || tower->getTowerType() == TOWER_TYPE::FROSTTOWER)
					{
						tower->setOpacity(100.f);
					}
					else
					{
						tower->setOpacity(255.f);
						CP_Vector tempPos = gameMap->getTile(CP_Input_GetMouseX(), CP_Input_GetMouseY()).pos;

						float dist = CP_Vector_Distance(tower->getPosition(), CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY()));
						if (dist <= 24.f)
						{
							if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
							{
								game.loseMoneys(tower->getUpgradeCosts());
								tower->levelUp();
							}
						}
				
					}
				}
				else if (game.currSelect != LEVELUP)
				{
					tower->setOpacity(255.f);
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
							
							if (projectileList[i]->getProjType() != PROJECTILE_TYPE::DAMAGEOVERTIME)
							{
								BaseProjectile* proj = projectileList[i];
								projectileList.erase(projectileList.begin() + i);
							}
							//delete proj;

							break;
						}
				
					}
				}

			}

			if (game.shouldShowWinscreen() || game.shouldShowLosescreen())
			{
				game.drawRect(CP_System_GetWindowWidth() * 0.5f, CP_System_GetWindowHeight() * 0.5f,
					CP_System_GetWindowWidth(), CP_System_GetWindowHeight(), 0.f, 0.f, CP_Color_Create(0, 0, 0, 125));

				game.back->Draw();

				if (game.back->IsClicked())
				{
					SceneManager::GetInstance()->ChangeScenes(Scenes::MAIN_MENU_SCENE);
					game.CleanUpGame();
				}

				if (game.shouldShowWinscreen())
				{
					CP_Settings_TextSize(game.getFontSize() * 4);
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawTextBox("You win!", CP_System_GetWindowWidth() * 0.25f, CP_System_GetWindowHeight() * 0.25f, sizeof("You win!") * game.getFontSize() * 4);
					CP_Settings_TextSize(game.getFontSize());
					CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
				}
				else
				{
					CP_Settings_TextSize(game.getFontSize() * 4);
					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Font_DrawTextBox("You lose", CP_System_GetWindowWidth() * 0.25f, CP_System_GetWindowHeight() * 0.25f, sizeof("You lose")* game.getFontSize() * 4);
					CP_Settings_TextSize(game.getFontSize());
					CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
				}
			}
		}

		void gameExit(void)
		{
		}


