#pragma once
#include "../../Utils/Button.h"
#include "../../Scenes/Game/Game.h"

/*!
@file       PauseMenu.h
@author     Chee Kang(l.cheekang)
@brief      This file contains declaration of functions and variables
			used for the pause menu class
*//*_______________________________________________________________________*/

class PauseMenu {
private:
	Game* game; // Pointer to the main game instance
	Button* resume; // Resume button
	Button* settings; // Settings button
	Button* quit; // Quit button
	//Button dimensions
    float buttonWidth = 200.0f;
    float buttonHeight = 60.0f;

public:
	PauseMenu(Game* g); // Constructor
	~PauseMenu(); // Destructor

	void ButtonInit(); // Initialize buttons
	void ButtonDraw(); // Draw buttons
	void HandleInput(); // Handle button clicks
    void Exit(); // Cleanup buttons
};

void PauseMenuInit();
void PauseMenuUpdate();
void PauseMenuExit();
