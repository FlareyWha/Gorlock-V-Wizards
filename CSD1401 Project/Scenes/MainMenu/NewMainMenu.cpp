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

CP_Font mainMenuFont;
Map* map;
SceneManager* scene;
NewMainMenu menu;
CP_TEXT_ALIGN_HORIZONTAL center = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_BASELINE;

void NewMainMenu::ButtonInit(void)
{
	//Load the image for the start button
	Button = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
	//first button
	buttonX1 = CP_System_GetWindowWidth() / 2;
	buttonY1 = CP_System_GetWindowHeight() / 2;
	//Second button
	buttonY2 = CP_System_GetWindowHeight() / 2 + 130;
	//third button
	buttonY3 = CP_System_GetWindowHeight() / 2 + 260;

}

void NewMainMenu::ButtonDraw()
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_TextAlignment(center, vertical);
	//first button
	CP_Image_Draw(Button, buttonX1, buttonY1, buttonWidth, buttonHeight, 255);
	CP_Font_DrawText("Start", buttonX1, buttonY1);
	//second button
	CP_Image_Draw(Button, buttonX1, buttonY2, buttonWidth, buttonHeight, 255);
	CP_Font_DrawText("Settings", buttonX1, buttonY2);
	//third button
	CP_Image_Draw(Button, buttonX1, buttonY3, buttonWidth, buttonHeight, 255);
	CP_Font_DrawText("Quit", buttonX1, buttonY3);
}

bool NewMainMenu::isButtonClicked()
{
	float mouseX = CP_Input_GetMouseWorldX();
	float mouseY = CP_Input_GetMouseWorldY();
	if (mouseX >= buttonX1 - buttonWidth / 2 && mouseX <= buttonX1 + buttonWidth / 2 &&
		mouseY >= buttonY1 - buttonHeight / 2 && mouseY <= buttonY1 + buttonHeight / 2 && CP_Input_MouseClicked())
	{
		scene->ChangeScenes(Scenes::GAME_SCENE);
	}
	else if (mouseX >= buttonX1 - buttonWidth / 2 && mouseX <= buttonX1 + buttonWidth / 2 &&
		mouseY >= buttonY2 - buttonHeight / 2 && mouseY <= buttonY2 + buttonHeight / 2 && CP_Input_MouseClicked())
	{
		scene->ChangeScenes(Scenes::SETTINGS_SCENE);
	}
	else if (mouseX >= buttonX1 - buttonWidth / 2 && mouseX <= buttonX1 + buttonWidth / 2 &&
		mouseY >= buttonY3 - buttonHeight / 2 && mouseY <= buttonY3 + buttonHeight / 2 && CP_Input_MouseClicked())
	{
		CP_Engine_Terminate();
	}
	return false;
}



void mainMenuInit(void) {
	mainMenuFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
	menu.ButtonInit();
	scene = SceneManager::GetInstance();
}

void mainMenuUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Font_Set(mainMenuFont);
	//Title
	CP_Font_DrawText("Main Menu", 100, 100);
	CP_Settings_TextSize(25.0f);
	//Draw Buttons
	menu.ButtonDraw();
	//Check for button clicks
	menu.isButtonClicked();
	
}

void mainMenuExit(void)
{
	//This stuff below should move to anywhere that terminates the game
	CP_Font_Free(mainMenuFont);
	
}
