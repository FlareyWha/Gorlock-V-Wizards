#include "Button.h"
#include "cprocessing.h"
#include <cstdio>

CP_Image Button::sprite = nullptr;
CP_Font Button::mainMenuFont = nullptr;

Button::Button(float x, float y, float width, float height, const char* text)
    : x(x), y(y), w(width), h(height), label(text)
{
    if (!sprite) {
        sprite = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
        if (!sprite) printf("ERROR: Failed to load button image!\n");
    }
}

void Button::Draw() const
{
    CP_Image_Draw(sprite, x, y, w, h, 255);
    CP_Font_Set(mainMenuFont);

    CP_Settings_TextSize(h * 0.45f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

    CP_Font_DrawText(label, x, y);
}

bool Button::IsHovered() const
{
    float mx = CP_Input_GetMouseX();
    float my = CP_Input_GetMouseY();
    return (mx > x - w / 2 && mx < x + w / 2 &&
        my > y - h / 2 && my < y + h / 2);
}

bool Button::IsClicked() const
{
    return IsHovered() && CP_Input_MouseClicked();
}

void Button::LoadResources() {
    if (!sprite) {
        sprite = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
        if (!sprite) printf("ERROR: Failed to load button image!\n");
    }
    if (!mainMenuFont) {
        mainMenuFont = CP_Font_Load("Assets/Fonts/KenneyFonts/Kenney Mini.ttf");
        if (!mainMenuFont) printf("ERROR: Failed to load button font!\n");
    }
}

void Button::FreeResources() {
    if (sprite) {
        CP_Image_Free(sprite);
        sprite = nullptr;
    }
    if (mainMenuFont) {
        CP_Font_Free(mainMenuFont);
        mainMenuFont = nullptr;
    }
}

void Button::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
}