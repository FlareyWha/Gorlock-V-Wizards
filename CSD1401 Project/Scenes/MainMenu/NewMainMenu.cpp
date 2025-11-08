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

CP_Font mainMenuFont;
Map* map;
SceneManager* scene;
NewMainMenu menu;
CP_TEXT_ALIGN_HORIZONTAL center = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_BASELINE;

void NewMainMenu::ButtonInit()
{
	float windowWidth = CP_System_GetWindowWidth();
	float windowHeight = CP_System_GetWindowHeight();

	// Animation starting positions (offscreen)
	buttonTopY = -windowHeight;
	buttonBottomY = windowHeight + buttonHeight;
	buttonRightX = windowWidth + buttonWidth;
	buttonLeftX = -buttonWidth;
	buttonTargetX = windowWidth / 2;

	buttonY1 = windowHeight / 2;
	buttonY2 = buttonY1 + 100;
	buttonY3 = buttonY1 + 300;
	buttonY4 = buttonY1 + 200;

	// Create buttons
	startButton = new Button(buttonRightX, buttonTopY, buttonWidth, buttonHeight, "Start");
	settingsButton = new Button(buttonLeftX, buttonY2, buttonWidth, buttonHeight, "Settings");
	mapEditorButton = new Button(buttonRightX, buttonY4, buttonWidth, buttonHeight, "Map Editor");
	quitButton = new Button(buttonLeftX, buttonBottomY, buttonWidth, buttonHeight, "Quit");
}

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
	quitButton->SetPosition(buttonLeftX, buttonBottomY);

	// Draw all buttons
	startButton->Draw();
	settingsButton->Draw();
	mapEditorButton->Draw();
	quitButton->Draw();
}

void NewMainMenu::HandleClicks()
{
	if (startButton->IsClicked())
		scene->ChangeScenes(Scenes::GAME_SCENE);

	else if (settingsButton->IsClicked())
		scene->ChangeScenes(Scenes::SETTINGS_SCENE);

	else if (mapEditorButton->IsClicked())
		scene->ChangeScenes(Scenes::MAP_EDITOR_SCENE);

	else if (quitButton->IsClicked())
		CP_Engine_Terminate();
}

void NewMainMenu::Exit()
{
	delete startButton;
	delete settingsButton;
	delete mapEditorButton;
	delete quitButton;

	// Optionally free the static image/font from Button
	// CP_Image_Free(Button::sprite);
	// CP_Font_Free(Button::mainMenuFont);
}


void mainMenuInit(void) {
	mainMenuFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
	menu.ButtonInit();
	scene = SceneManager::GetInstance();
}

void mainMenuUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	// Title
	CP_Font_Set(mainMenuFont);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("Main Menu", 100, 100);

	// Buttons
	menu.ButtonDraw();
	menu.HandleClicks();
}

void mainMenuExit(void)
{
	//This stuff below should move to anywhere that terminates the game
	CP_Font_Free(mainMenuFont);
	
	SoundManager::GetInstance()->stopBGM();
}
