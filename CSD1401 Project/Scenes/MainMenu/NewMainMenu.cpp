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
	//Calculate button positions based on window size
	float windowWidth = CP_System_GetWindowWidth();
	float windowHeight = CP_System_GetWindowHeight();
	//Buttons X position
	buttonTargetX = windowWidth / 2;
	buttonCurrentX = windowWidth + buttonWidth; // Start off-screen (right)
	//Buttons Y position
	buttonY1 = windowHeight / 2;
	buttonY2 = buttonY1 + 130;
	buttonY3 = buttonY1 + 260;

}

void NewMainMenu::ButtonDraw()
{
	// Move buttons toward the center smoothly
	float dt = CP_System_GetDt(); // time since last frame
	float distance = buttonTargetX - buttonCurrentX;

	// simple easing (slide)
	if (fabs(distance) > 1.0f)
		buttonCurrentX += distance * 5.0f * dt; // adjust 5.0f for smoothness

	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_TextAlignment(center, vertical);

	// Draw buttons at the animated X position
	CP_Image_Draw(Button, buttonCurrentX, buttonY1, buttonWidth, buttonHeight, 255);
	CP_Font_DrawText("Start", buttonCurrentX, buttonY1);

	CP_Image_Draw(Button, buttonCurrentX, buttonY2, buttonWidth, buttonHeight, 255);
	CP_Font_DrawText("Settings", buttonCurrentX, buttonY2);

	CP_Image_Draw(Button, buttonCurrentX, buttonY3, buttonWidth, buttonHeight, 255);
	CP_Font_DrawText("Quit", buttonCurrentX, buttonY3);
}

bool NewMainMenu::isButtonClicked()
{
	float mouseX = CP_Input_GetMouseWorldX();
	float mouseY = CP_Input_GetMouseWorldY();

	auto withinButton = [&](float bx, float by) {
		return mouseX >= bx - buttonWidth / 2 && mouseX <= bx + buttonWidth / 2 &&
			mouseY >= by - buttonHeight / 2 && mouseY <= by + buttonHeight / 2;
		};

	if (withinButton(buttonCurrentX, buttonY1) && CP_Input_MouseClicked())
	{
		scene->ChangeScenes(Scenes::GAME_SCENE); 
	}
	else if (withinButton(buttonCurrentX, buttonY2) && CP_Input_MouseClicked()) 
	{
		scene->ChangeScenes(Scenes::SETTINGS_SCENE);
	}
	else if (withinButton(buttonCurrentX, buttonY3) && CP_Input_MouseClicked()) {
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
