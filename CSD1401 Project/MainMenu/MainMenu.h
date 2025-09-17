/*!
@file       MainMenu.h	
@author     Lim Chee Kang (l.cheekang)
@brief      This file contains function definitions which manages the main menu
*//*_______________________________________________________________________*/

#pragma once
#include "cprocessing.h"
#include <iostream>
class MainMenu
{

protected:
	
private:
	CP_Image StartButton;
	float buttonX = 0;
	float buttonY = 0;
	float buttonWidth = 250;
	float buttonHeight = 45;

public:
	void StartButtonInit();
	void StartButtonDraw();
	bool isButtonClicked();
};

