#include "cprocessing.h"
#include "Settings.h"
#include "../../GUI/Game.h"

CP_Font myFont;

void settingsInit(void)
{
	myFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
}

void settingsUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Font_Set(myFont);
	CP_Font_DrawText("Settings", 100, 100);
}

void settingsExit(void)
{
	CP_Font_Free(myFont);
}
