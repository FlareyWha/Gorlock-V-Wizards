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
public:
	void StartButtonInit(void);
	CP_Image GetStartButton() const;
};

