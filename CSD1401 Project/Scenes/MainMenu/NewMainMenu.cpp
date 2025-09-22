#include "cprocessing.h"
#include "NewMainMenu.h"
#include <iostream>

CP_Font mainMenuFont;

void NewMainMenu::StartButtonInit(void)
{
	StartButton = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
	buttonX = CP_System_GetWindowWidth() / 2;
	buttonY = CP_System_GetWindowHeight() / 2;



}

void NewMainMenu::StartButtonDraw()
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(StartButton, buttonX, buttonY, buttonWidth, buttonHeight, 255);

}

bool NewMainMenu::isButtonClicked()
{
	float mouseX = CP_Input_GetMouseWorldX();
	float mouseY = CP_Input_GetMouseWorldY();
	if (mouseX >= buttonX - buttonWidth / 2 && mouseX <= buttonX + buttonWidth / 2 &&
		mouseY >= buttonY - buttonHeight / 2 && mouseY <= buttonY + buttonHeight / 2)
	{
		if (CP_Input_MouseClicked())
		{
			CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 255));
			return true;
		}
	}
	return false;
}

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
