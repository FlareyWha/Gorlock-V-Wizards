#include "cprocessing.h"
#include "Scenes/Settings/Settings.h"
#include "System/SceneManager.h"
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
	logo = CP_Image_Load("Assets/Images/DigiPen_Singapore_WEB_RED.png");
	CP_System_SetWindowSize(1600, 900);
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	mainFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");

	sceneManager = SceneManager::GetInstance();
	settingsManager = SettingsManager::GetInstance();

	settingsManager->readVolumeSettings();
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
}

void game_exit(void)
{
	CP_Image_Free(logo);
	sceneManager->DestroyInstance();
}


int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run(0);
	return 0;
}