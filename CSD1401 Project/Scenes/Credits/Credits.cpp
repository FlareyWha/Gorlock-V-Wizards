#include "Credits.h"  
#include <stdio.h>
#include "../../System/SceneManager.h"
#include "../../Utils/Button.h"
CP_Image creditsImage;
float yPos = 0;
SceneManager* scenery;
Button backButton(0, 0, 0, 0, "");
CP_Font creditsFont;
float scrollSpeed = 100;
void creditsInit(void)
{
	creditsImage = CP_Image_Load("../../Assets/Credits/Credits.png");
	yPos = CP_System_GetWindowHeight();
	scenery = SceneManager::GetInstance();
	creditsFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
	backButton = Button(150, 850, 150, 50, "Back");
}

void creditsUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		scrollSpeed = 500.f;
	}
	else
		scrollSpeed = 100.f;
	yPos -= scrollSpeed * CP_System_GetDt();

	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(creditsImage,0, yPos,CP_Image_GetWidth(creditsImage),CP_Image_GetHeight(creditsImage),255);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	backButton.Draw();
	if(backButton.IsClicked()) {  // dot, not arrow
		Scenes previous = scenery->GetPreviousScene();
		scenery->ChangeScenes(previous);
	}
}    

void creditsExit(void)
{
	CP_Font_Free(creditsFont);
	CP_Image_Free(creditsImage);
}