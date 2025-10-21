#pragma once
#include "cprocessing.h"
#include <iostream>

class NewMainMenu
{

protected:

private:
	CP_Image Button;
	CP_Font mainMenuFont;
	float buttonX1 = 0;
	float buttonY1 = 0;

	float buttonWidth = 250;
	float buttonHeight = 60;

	float buttonY2 = 0;
	float buttonY3 = 0;

public:
	void ButtonInit();
	void ButtonDraw();
	bool isButtonClicked();
};

void mainMenuInit(void);
void mainMenuUpdate(void);
void mainMenuExit(void);
