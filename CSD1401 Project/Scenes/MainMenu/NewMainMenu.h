#pragma once
#include "cprocessing.h"
#include "../../Utils/Button.h"

/*!
@file       NewMainMenu.h
@author     Chee Kang(l.cheekang)
@brief      This file contains declaration of functions and variables
			used for the new main menu class
*//*_______________________________________________________________________*/


class NewMainMenu {
public:
	void ButtonInit(); // Initialize buttons
	void ButtonDraw(); // Draw buttons
	void HandleClicks(); // Handle button clicks
	void Exit(); // Cleanup buttons

protected:
	Button* startButton; // Start Game button
	Button* settingsButton; //settings button
	Button* mapEditorButton; // Map Editor button
	Button* creditsButton; // Credits button
	Button* quitButton; //Quit button

	//Button dimensions
    float buttonWidth = 250;
    float buttonHeight = 70;

	// Button animation positions
    float buttonTargetX;
    float buttonTopY, buttonBottomY, buttonLeftX, buttonRightX;
    float buttonY1, buttonY2, buttonY3, buttonY4 , buttonY5;
};

void mainMenuInit(void);
void mainMenuUpdate(void);
void mainMenuExit(void);
