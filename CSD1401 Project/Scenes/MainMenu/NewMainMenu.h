#pragma once
#include "cprocessing.h"
#include "../../Utils/Button.h"

class NewMainMenu {
public:
    void ButtonInit();
    void ButtonDraw();
    void HandleClicks();
    void Exit();

protected:
    Button* startButton;
    Button* settingsButton;
    Button* mapEditorButton;
    Button* quitButton;

    float buttonWidth = 250;
    float buttonHeight = 70;

    // Offscreen animation positions
    float buttonTargetX;
    float buttonTopY, buttonBottomY, buttonLeftX, buttonRightX;
    float buttonY1, buttonY2, buttonY3, buttonY4;
};

void mainMenuInit(void);
void mainMenuUpdate(void);
void mainMenuExit(void);
