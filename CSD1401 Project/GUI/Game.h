/*!
@file       Game.h
@author     Chew Zavier(c.zavier)
@brief      This file contains functions to draw the Game Interface.
*//*_______________________________________________________________________*/

#pragma once
#include "cprocessing.h"

void gameInit(void);
void gameUpdate(void);
void gameExit(void);
void drawRect(float posX, float posY, float rectWidth, float rectHeight, float angle = 0.0f,float cornerRadius = 0.0f, CP_Color rectColor = { 100,100,100,255 });
void drawText(const char* text,float xPos, float yPos);
void setFontSize(float size);
float getFontSize();


