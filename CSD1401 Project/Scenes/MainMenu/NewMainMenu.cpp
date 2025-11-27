#include "cprocessing.h"
#include "../../Towers/BaseTower.h"
#include "../../System/Map.h"
#include "../../Scenes/Settings/Settings.h"
#include "../../Scenes/MainMenu/NewMainMenu.h"
#include "../../Scenes/Game/Game.h"
#include "../../Scenes/MapEditor/MapEditor.h"
#include "../../System/SceneManager.h"
#include "../../System/SoundManager.h"
#include "../../System/SettingsManager.h"
#include "../../Utils/Button.h"

/*!
@file       NewMainMenu.cpp
@author     Chee Kang(l.cheekang)
@brief      This file contains the definitions of functions to draw the main menu.
*//*_______________________________________________________________________*/

// Main menu assets
CP_Image mainLogo;
CP_Font mainMenuFont;
Map* map;
SceneManager* scene;
NewMainMenu menu;
CP_TEXT_ALIGN_HORIZONTAL center = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_BASELINE;

/**
 @brief Button Initialization
 @return void
 */
void NewMainMenu::ButtonInit()
{
	// Get window dimensions
	float windowWidth = (float)CP_System_GetWindowWidth();
	float windowHeight = (float)CP_System_GetWindowHeight();

	// Animation starting positions (offscreen)
	buttonTopY = -windowHeight;
	buttonBottomY = windowHeight + buttonHeight;
	buttonRightX = windowWidth + buttonWidth;
	buttonLeftX = -buttonWidth;
	buttonTargetX = windowWidth / 2;

	buttonY1 = windowHeight / 2;
	buttonY2 = buttonY1 + 100;
	buttonY3 = buttonY1 + 400;
	buttonY4 = buttonY1 + 200;
	buttonY5 = buttonY1 + 300;

	// Create buttons
	startButton = new Button(buttonRightX, buttonTopY, buttonWidth, buttonHeight, "Start");
	settingsButton = new Button(buttonLeftX, buttonY2, buttonWidth, buttonHeight, "Settings");
	mapEditorButton = new Button(buttonRightX, buttonY4, buttonWidth, buttonHeight, "Map Editor");
	creditsButton = new Button(buttonRightX, buttonY5, buttonWidth, buttonHeight, "Credits");
	quitButton = new Button(buttonLeftX, buttonBottomY, buttonWidth, buttonHeight, "Quit");
}

/**
 @brief Button Drawing and Animation
 @return void
 */
void NewMainMenu::ButtonDraw()
{
	float dt = CP_System_GetDt();

	// Simple easing for sliding in
	buttonTopY += (buttonY1 - buttonTopY) * 2.3f * dt;
	buttonBottomY += (buttonY3 - buttonBottomY) * 1.0f * dt;
	buttonRightX += (buttonTargetX - buttonRightX) * 1.0f * dt;
	buttonLeftX += (buttonTargetX - buttonLeftX) * 1.5f * dt;

	// Update button positions
	startButton->SetPosition(buttonRightX, buttonTopY);
	settingsButton->SetPosition(buttonLeftX, buttonY2);
	mapEditorButton->SetPosition(buttonRightX, buttonY4);
	creditsButton->SetPosition(buttonLeftX, buttonY5);
	quitButton->SetPosition(buttonRightX, buttonBottomY);

	// Draw all buttons
	startButton->Draw();
	settingsButton->Draw();
	mapEditorButton->Draw();
	creditsButton->Draw();
	quitButton->Draw();
}

/**
 @brief Check and handle button clicks
 @return void
 */
void NewMainMenu::HandleClicks()
{
	// Handle button clicks
	if (startButton->IsClicked())
	{
		Map::GetInstance()->setLoadEditedMap(false);
		SoundManager::GetInstance()->stopBGM();
		scene->ChangeScenes(Scenes::GAME_SCENE);
	}

	else if (settingsButton->IsClicked())
		scene->ChangeScenes(Scenes::SETTINGS_SCENE);

	else if (mapEditorButton->IsClicked())
		scene->ChangeScenes(Scenes::MAP_EDITOR_SCENE);

	else if (creditsButton->IsClicked())
		scene->ChangeScenes(Scenes::CREDITS_SCENE);
	else if (quitButton->IsClicked())
	{
		SoundManager::GetInstance()->freeAllSounds();
		SoundManager::GetInstance()->DestroyInstance();
		SettingsManager::GetInstance()->DestroyInstance();
		Map::GetInstance()->resetMap(true);
		Map::GetInstance()->freeImages(true);
		Map::GetInstance()->DestroyInstance();
		CP_Engine_Terminate();
	}
}

/**
 @brief When exiting the main menu, free buttons
 @return void
 */
void NewMainMenu::Exit()
{
	// Free buttons
	delete startButton;
	delete settingsButton;
	delete mapEditorButton;
	delete quitButton;
}

/**
 @brief Initialize the main menu
 @param void
 @return void
 */
void mainMenuInit(void) {
	// Load assets
	mainMenuFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
	mainLogo = CP_Image_Load("Assets/Images/mainmenu_logo.png");
	menu.ButtonInit();
	scene = SceneManager::GetInstance();
	SoundManager::GetInstance()->playBGM(MAIN_MENU_BGM);
}

/**
 @brief Update the main menu
 @return void
 */
void mainMenuUpdate()
{
	// Clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Image_Draw(mainLogo, (float)CP_System_GetWindowWidth() * 0.5f, (float)CP_System_GetWindowHeight() * 0.25f, 184.f * 4, 104.f * 4, 255);

	// Title
	CP_Font_Set(mainMenuFont);
	CP_Settings_TextSize(25.0f);

	// Buttons
	menu.ButtonDraw();
	menu.HandleClicks();
}

/**
 @brief Free main menu assets on exit
 @return void
 */
void mainMenuExit(void)
{
	CP_Font_Free(mainMenuFont);
}
