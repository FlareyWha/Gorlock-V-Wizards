#include "cprocessing.h"
#include "Towers/BaseTower.h"
#include "System/Map.h"
#include "Scenes/Settings/Settings.h"
#include "Scenes/MainMenu/NewMainMenu.h"
#include "Scenes/Game/Game.h"
#include "Scenes/MapEditor/MapEditor.h"
#include "System/SceneManager.h"

CP_Image logo;
BaseTower tower;

Map* map;

float degrees = 0.0f;
NewMainMenu menu;
CP_Font mainFont;
SceneManager* sceneManager;

void game_init(void)
{
	tower.setImage(CP_Image_Load("Assets/kenney_tiny-battle/Tiles/tile_0152.png"));

	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	//logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(1600, 900);
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	mainFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");

	sceneManager = SceneManager::GetInstance();
	
	// Initialize Main Menu
	//menu.StartButtonInit();

	map = Map::GetInstance();
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	degrees = CP_Math_Degrees(atan2(CP_Input_GetMouseWorldY() - CP_System_GetWindowHeight() / 2,
		CP_Input_GetMouseWorldX() - CP_System_GetWindowWidth() / 2));

	//CP_Image_Draw(tower.getImage(), 0.f, 0.f, CP_Image_GetWidth(tower.getImage()), CP_Image_GetHeight(tower.getImage()), 255);
	/*CP_Image_DrawAdvanced(tower.getImage(), CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2,
		CP_Image_GetWidth(tower.getImage()) * 10, CP_Image_GetHeight(tower.getImage()) * 10, 255, degrees);*/

	menu.StartButtonDraw();
	menu.isButtonClicked();
	
	CP_Font_Set(mainFont);
	CP_Font_DrawText("Test scene", 100, 100);
	CP_Font_DrawText("Press 1 for main menu", 100, 200);
	CP_Font_DrawText("Press 2 for game scene", 100, 250);
	CP_Font_DrawText("Press 3 for settings scene", 100, 300);
	CP_Font_DrawText("Press 4 for map editor scene", 100, 350);

	sceneManager->ChangeScenes(Scenes::GAME_SCENE);

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
}

void game_exit(void)
{
	CP_Image_Free(logo);
	sceneManager->DestroyInstance();

	map->resetMap(false);
	map->freeImages();
	map->DestroyInstance(false);
}




int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run(1);
	return 0;
}