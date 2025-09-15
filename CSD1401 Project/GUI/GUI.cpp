#include "GUI.h"
#include "cprocessing.h"
#include <iostream>
/*!
@file       GUI.cpp
@author     Chew Zavier(c.zavier)
@brief      This file contains the definitions of functions to draw the Graphical User Interface (GUI).
*//*_______________________________________________________________________*/

void GUI::guiInit(void)
{	
	font = CP_Font_Load(FILE_PATH);
	if (!CP_Font_Load(FILE_PATH))
	{
		throw "File path invalid, please double check.";
	}
	CP_Font_Set(font);

	CP_Settings_TextSize(12.0f);
	CP_Font_DrawText("YIBBBEEE", 10, 10);
}

void GUI::drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle, float cornerRadius, CP_Color rectColor)
{
	CP_Settings_Fill(rectColor);
	CP_Graphics_DrawRectAdvanced(posX, posY, rectWidth, rectHeight, angle,cornerRadius);
}

void GUI::setFontSize(float size)
{
	fontSize = size;
}

float GUI::getFontSize()
{
	return fontSize;
}
