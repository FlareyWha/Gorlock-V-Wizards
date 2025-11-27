#pragma once
#include "cprocessing.h"

/*!
@file       Button.h
@author     Chee Kang(l.cheekang)
@brief      This file contains declaration of the Button class
*//*_______________________________________________________________________*/

class Button {
public:
	Button(float x, float y, float w, float h, const char* text); // Constructor for button

	void Draw() const; // Draw the button
	bool IsHovered() const; // Check if mouse is over the button
	bool IsClicked() const; // Check if button is clicked
	void SetPosition(float x, float y); // Set button position

    static void LoadResources();   // Load image/font once
    static void FreeResources();   // Free image/font once

private:
	float x, y, w, h; // Position and size
	const char* label; // Button label text

	// Static shared resources
    static CP_Image sprite;
    static CP_Font mainMenuFont;
};


