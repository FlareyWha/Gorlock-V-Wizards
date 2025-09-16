/*!
@file       MainMenu.h	
@author     Lim Chee Kang (l.cheekang)
@brief      This file contains function definitions which declares themain menu
*//*_______________________________________________________________________*/

#include "MainMenu.h"
#include "cprocessing.h"
#include <iostream>

void MainMenu::StartButtonInit(void)
{
	StartButton = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
	buttonX = CP_System_GetWindowWidth() / 2;
	buttonY = CP_System_GetWindowHeight() / 2;



}	

void MainMenu::StartButtonDraw()
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(StartButton, buttonX, buttonY, buttonWidth, buttonHeight, 255);
	
}

bool MainMenu::isButtonClicked()
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
