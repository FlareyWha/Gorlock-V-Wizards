/*!
@file       GUI.h
@author     Chew Zavier(c.zavier)
@brief      This file contains functions to draw the Game Interface.
*//*_______________________________________________________________________*/

#pragma once
#include <string>
#include "cprocessing.h"
class GUI
{
	protected:
		CP_Font font;
	private :
		const char* FILE_PATH = "./Assets/Fonts/KenneyFonts/Kenney Mini.ttf";
		float fontSize = 12.0f;
	public:
		void guiInit(void);
		void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle = 0.0f,float cornerRadius = 0.0f, CP_Color rectColor = { 255,255,255,255 });
		void setFontSize(float size);
		float getFontSize();

};

