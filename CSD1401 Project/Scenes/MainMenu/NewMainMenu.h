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

	float buttonTargetX = 0;
	float buttonRightX = 0;
	float buttonLeftX = 0;
	float buttonTopY = 0;
	float buttonBottomY = 0;

public:
	void ButtonInit();
	void ButtonDraw();
	bool isButtonClicked();
};

void mainMenuInit(void);
void mainMenuUpdate(void);
void mainMenuExit(void);
