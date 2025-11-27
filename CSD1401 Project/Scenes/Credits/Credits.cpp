#include "Credits.h"  
#include <stdio.h>
#include "../../System/SceneManager.h"
#include "../../Utils/Button.h"
/*!
@file       Credits.cpp 
@author     Chew Zavier (c.zavier)
@brief		Contains definitions of functions used by Credits scene
*//*_______________________________________________________________________*/
CP_Image creditsImage;//image of the actual credits
float yPos = 0;
SceneManager* scenery;
Button backButton(0, 0, 0, 0, "");
CP_Font creditsFont;
float scrollSpeed = 100;//speed at which it scrolls
void creditsInit(void)
{
	creditsImage = CP_Image_Load("../../Assets/Credits/Credits.png");
	yPos = (float)CP_System_GetWindowHeight();//spawn the image outside of screen for scrollinge effect
	scenery = SceneManager::GetInstance();
	creditsFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
	backButton = Button(150, 850, 150, 50, "Back");
}

void creditsUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	if (CP_Input_MouseDown(MOUSE_BUTTON_1))
	{
		scrollSpeed = 500.f;//increase scrollspeed if LMB is down
	}
	else
		scrollSpeed = 100.f;//normal scroll speed
	yPos -= scrollSpeed * CP_System_GetDt();//just push the image up

	CP_Settings_ImageMode(CP_POSITION_CORNER);//use the corner to draw the image
	CP_Image_Draw(creditsImage,0, yPos, (float)CP_Image_GetWidth(creditsImage), (float)CP_Image_GetHeight(creditsImage), 255);//draw the image out 
	CP_Settings_ImageMode(CP_POSITION_CENTER);//reset it back to center
	backButton.Draw();//draw the button
	if(backButton.IsClicked() || yPos <= - CP_Image_GetHeight(creditsImage) ) {  // dot, not arrow
		Scenes previous = scenery->GetPreviousScene();
		scenery->ChangeScenes(previous);
	}
}    

void creditsExit(void)
{
	CP_Font_Free(creditsFont);//free font
	CP_Image_Free(creditsImage);//free image
}