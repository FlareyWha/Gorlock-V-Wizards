#include "cprocessing.h"
#include "Towers/BaseTower.h"
#include "System/Map.h"
#include "MainMenu/MainMenu.h"
#include "Scenes/Settings/Settings.h"
#include "Scenes/MainMenu/NewMainMenu.h"
#include "Scenes/Game/Game.h"
CP_Image logo;
BaseTower tower;

Map* map;

float degrees = 0.0f;
MainMenu menu;
CP_Font mainFont;
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

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	else if (CP_Input_KeyDown(KEY_1))
	{
		CP_Engine_SetNextGameState(mainMenuInit, mainMenuUpdate, mainMenuExit);
	}
	else if (CP_Input_KeyDown(KEY_2))
	{
		//CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
	}
	else if (CP_Input_KeyDown(KEY_3))
	{
		CP_Engine_SetNextGameState(settingsInit, settingsUpdate, settingsExit);
	}
}

void game_exit(void)
{
	CP_Image_Free(logo);

	map->DestroyInstance();
}




int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run(0);
	return 0;
}