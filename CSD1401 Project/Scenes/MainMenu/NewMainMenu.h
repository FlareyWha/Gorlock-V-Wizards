#pragma once
#include "cprocessing.h"
#include <iostream>

class NewMainMenu
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

void mainMenuInit(void);
void mainMenuUpdate(void);
void mainMenuExit(void);
