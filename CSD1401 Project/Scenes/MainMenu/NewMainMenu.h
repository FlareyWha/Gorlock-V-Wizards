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
    float buttonTargetX = 0.f;
    float buttonTopY = 0.f, buttonBottomY = 0.f, buttonLeftX = 0.f, buttonRightX = 0.f;
    float buttonY1 = 0.f, buttonY2 = 0.f, buttonY3 = 0.f, buttonY4 = 0.f, buttonY5 = 0.f;

public:
	NewMainMenu(); //Constructor
};

void mainMenuInit(void);
void mainMenuUpdate(void);
void mainMenuExit(void);
