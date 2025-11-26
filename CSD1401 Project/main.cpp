#include "cprocessing.h"
#include "Towers/BaseTower.h"
#include "Towers/FireTower.h"
#include "Towers/IceTower.h"
#include "Towers/WindTower.h"
#include "Towers/LightningTower.h"
#include "System/Map.h"
#include "Scenes/Settings/Settings.h"
#include "Scenes/MainMenu/NewMainMenu.h"
#include "Scenes/Game/Game.h"
#include "Scenes/MapEditor/MapEditor.h"
#include "System/SceneManager.h"
#include "System/SoundManager.h"
#include "System/SettingsManager.h"

SettingsManager* settingsManager;

CP_Image logo;
float splashscreenAlpha = 255.f;
float splashscreenTimer = 3.f;
float lerpdirection = 0.f;

CP_Font mainFont;
SceneManager* sceneManager;

void game_init(void)
{
	//Test
	logo = CP_Image_Load("Assets/Images/DigiPen_Singapore_WEB_RED.png");
	CP_System_SetWindowSize(1600, 900);
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	mainFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");

	sceneManager = SceneManager::GetInstance();
	settingsManager = SettingsManager::GetInstance();

	settingsManager->readVolumeSettings();
	
	// Initialize Main Menu
	//menu.StartButtonInit();
	//sceneManager->ChangeScenes(Scenes::MAIN_MENU_SCENE);
	//map = Map::GetInstance();
}

void game_update(void)
{		
	lerpdirection += CP_System_GetDt();

	// Lerp rotation and draw image
	splashscreenAlpha = CP_Math_LerpFloat(0.0f, 255.0f, lerpdirection);
	splashscreenTimer -= 1 * CP_System_GetDt();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(logo, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, 1525.f * 0.75f, 445.f * 0.75f , (int)splashscreenAlpha);

	if (splashscreenTimer <= 0.f)
	{
		sceneManager->ChangeScenes(Scenes::MAIN_MENU_SCENE);
	}

	/*
	CP_Font_Set(mainFont);
	CP_Font_DrawText("Test scene", 100, 100);
	CP_Font_DrawText("Press 1 for main menu", 100, 200);
	CP_Font_DrawText("Press 2 for game scene", 100, 250);
	CP_Font_DrawText("Press 3 for settings scene", 100, 300);
	CP_Font_DrawText("Press 4 for map editor scene", 100, 350);

	//sceneManager->ChangeScenes(Scenes::GAME_SCENE);

	//soundManager->playBGM(TEST_BGM);
	*/

	/*
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	else if (CP_Input_KeyDown(KEY_1))
	{
		sceneManager->ChangeScenes(Scenes::MAIN_MENU_SCENE);
	}
	else if (CP_Input_KeyDown(KEY_2))
	{
		sceneManager->ChangeScenes(Scenes::GAME_SCENE);
	}
	else if (CP_Input_KeyDown(KEY_3))
	{
		sceneManager->ChangeScenes(Scenes::SETTINGS_SCENE);
	}
	else if (CP_Input_KeyDown(KEY_4))
	{
		sceneManager->ChangeScenes(Scenes::MAP_EDITOR_SCENE);
	}
	else if (CP_Input_KeyTriggered(KEY_5))
	{
		soundManager->playSFX(TEST_SFX);
	}
	*/
	if (CP_Input_KeyTriggered(KEY_5))
	{
		SoundManager::GetInstance()->playSFX(TEST_SFX);
	}
}

void game_exit(void)
{
	CP_Image_Free(logo);
	sceneManager->DestroyInstance();

	//This stuff below should move to anywhere that terminates the game
	//map->resetMap(false);
	//map->freeImages(false);
	//map->DestroyInstance(false);
}


int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run(0);
	return 0;
}