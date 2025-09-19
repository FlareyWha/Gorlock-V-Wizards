#include "cprocessing.h"
#include "NewMainMenu.h"

CP_Font mainMenuFont;

void mainMenuInit(void) {
	mainMenuFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
}

void mainMenuUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Font_Set(mainMenuFont);
	CP_Font_DrawText("Main Menu", 100, 100);
}

void mainMenuExit(void)
{
	CP_Font_Free(mainMenuFont);
}
