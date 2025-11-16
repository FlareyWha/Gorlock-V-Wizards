#pragma once
#include "../../Utils/Button.h"
#include "../../Scenes/Game/Game.h"

class PauseMenu {
private:
    Game* game;
    Button* resume;
    Button* settings;
    Button* quit;
    float buttonWidth = 200.0f;
    float buttonHeight = 60.0f;

public:
    PauseMenu(Game* g);
    ~PauseMenu();

    void ButtonInit();
    void ButtonDraw();
    void HandleInput();
    void Exit();
};

void PauseMenuInit();
void PauseMenuUpdate();
void PauseMenuExit();
