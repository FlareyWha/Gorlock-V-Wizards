//#include "Game.h"
#include "cprocessing.h"
#include <iostream>
#include <string>
/*!
@file       Game.cpp
@author     Chew Zavier(c.zavier)
@brief      This file contains the definitions of functions to draw the Graphical User Interface (game).
*//*_______________________________________________________________________*/

CP_Font font;
int health = 10;
const char* FILE_PATH = "./Assets/Fonts/KenneyFonts/Kenney Mini.ttf";
float fontSize = 12.0f;

void gameInit(void)
{	
	font = CP_Font_Load(FILE_PATH);
	if (!CP_Font_Load(FILE_PATH))
	{
		throw "File path invalid, please double check.";
	}
	CP_Font_Set(font);

	CP_Settings_TextSize(fontSize);
	//CP_Font_DrawText("YIBBBEEE", 10, 10);
}

void gameUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 101, 101, 255));
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		health--;
		drawText("Health" + health, 100, 100);
	}
	//drawText("hoorah",CP_Input_GetMouseX(), CP_Input_GetMouseY());
}

void gameExit(void)
{
	CP_Font_Free(font);
}

void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle, float cornerRadius, CP_Color rectColor)
{
	CP_Settings_Fill(CP_Color_Create(255,255,255,255));
	CP_Graphics_DrawRectAdvanced(posX, posY, rectWidth, rectHeight, angle,cornerRadius);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
}

void drawText(const char* text, float xPos,float yPos)
{
	CP_Font_DrawTextBox(text, xPos, yPos, sizeof(text) * fontSize);
}

void setFontSize(float size)
{
	fontSize = size;
}

float getFontSize()
{
	return fontSize;
}
