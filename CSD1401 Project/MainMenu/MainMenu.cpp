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
	CP_Settings_ImageMode(CP_POSITION_CENTER);


}	

CP_Image MainMenu::GetStartButton() const
{
	return StartButton;
}
