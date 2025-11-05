#pragma once
#include "cprocessing.h"

class Button {
public:
    Button(float x, float y, float w, float h, const char* text);

    void Draw() const;
    bool IsHovered() const;
    bool IsClicked() const;
    void SetPosition(float x, float y);

    static void LoadResources();   // Load image/font once
    static void FreeResources();   // Free image/font once

private:
    float x, y, w, h;
    const char* label;

    static CP_Image sprite;
    static CP_Font mainMenuFont;
};


