#include "Button.h"
#include "cprocessing.h"
#include <cstdio>

/*!
@file       Button.cpp
@author     Chee Kang(l.cheekang)
@brief      This file contains the definitions of functions for the Button class.
*//*_______________________________________________________________________*/

// Static member initialization
CP_Image Button::sprite = nullptr;
CP_Font Button::mainMenuFont = nullptr;

/**
 @brief Button Constructor
 @param x X position of the button
 @param y Y position of the button
 @param width Width of the button
 @param height Height of the button
 @param text Label text of the button
 @return void
 */
Button::Button(float x, float y, float width, float height, const char* text)
    : x(x), y(y), w(width), h(height), label(text)
	// Load resources if not already loaded
{
    if (!sprite) {
        sprite = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
        if (!sprite) printf("ERROR: Failed to load button image!\n");
    }
}

/**
 @brief Button Draw Method
 @return void
 */
void Button::Draw() const // Draw the button
{
    CP_Image_Draw(sprite, x, y, w, h, 255);
    CP_Font_Set(mainMenuFont);

    CP_Settings_TextSize(h * 0.45f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

    CP_Font_DrawText(label, x, y);
}

/**
 @brief When mouse is over the button
 @return void
 */
bool Button::IsHovered() const // Check if mouse is over the button
{
    float mx = CP_Input_GetMouseX();
    float my = CP_Input_GetMouseY();
    return (mx > x - w / 2 && mx < x + w / 2 &&
        my > y - h / 2 && my < y + h / 2);
}

/**
 @brief When button is clicked
 @return bool
 */
bool Button::IsClicked() const // Check if button is clicked
{
    return IsHovered() && CP_Input_MouseClicked();
}

/**
 @brief Check and load resources once
 @return void
 */
void Button::LoadResources() { // Load image and font resources
    if (!sprite) {
        sprite = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
        if (!sprite) printf("ERROR: Failed to load button image!\n");
    }
    if (!mainMenuFont) {
        mainMenuFont = CP_Font_Load("Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
        if (!mainMenuFont) printf("ERROR: Failed to load button font!\n");
    }
}

/**
 @brief Check and free resources once
 @return void
 */
void Button::FreeResources() { // Free image and font resources
    if (sprite) {
        CP_Image_Free(sprite);
        sprite = nullptr;
    }
    if (mainMenuFont) {
        CP_Font_Free(mainMenuFont);
        mainMenuFont = nullptr;
    }
}

/**
 @brief sets new button position
 @return void
 */
void Button::SetPosition(float newX, float newY) { // Set button position
    x = newX;
    y = newY;
}