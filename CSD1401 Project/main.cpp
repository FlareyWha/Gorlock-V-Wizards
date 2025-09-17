#include "cprocessing.h"
#include "Towers/BaseTower.h"
#include "System/Map.h"

#include "GUI/GUI.h"
CP_Image logo;

BaseTower tower;

Map* map;

float degrees = 0.0f;

GUI gui;
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

	gui.guiInit();

	map = Map::GetInstance();
}

void game_update(void)
{
	degrees = CP_Math_Degrees(atan2(CP_Input_GetMouseWorldY() - CP_System_GetWindowHeight() / 2,
		CP_Input_GetMouseWorldX() - CP_System_GetWindowWidth() / 2));

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//CP_Image_Draw(tower.getImage(), 0.f, 0.f, CP_Image_GetWidth(tower.getImage()), CP_Image_GetHeight(tower.getImage()), 255);
	CP_Image_DrawAdvanced(tower.getImage(), CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2,
		CP_Image_GetWidth(tower.getImage()) * 10, CP_Image_GetHeight(tower.getImage()) * 10, 255, degrees);

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
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