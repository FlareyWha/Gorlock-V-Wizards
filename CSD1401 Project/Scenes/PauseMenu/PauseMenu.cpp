#include "PauseMenu.h"
#include "../../System/SceneManager.h"
#include <cprocessing.h>

extern Game game;
PauseMenu pauseMenu(&game);

PauseMenu::PauseMenu(Game* g) : game(g), resume(nullptr), settings(nullptr), quit(nullptr) {}
PauseMenu::~PauseMenu() { Exit(); }

void PauseMenu::ButtonInit() {
    float midX = CP_System_GetWindowWidth() / 2.0f;
    float midY = CP_System_GetWindowHeight() / 2.0f;
    resume = new Button(midX, midY - 50, buttonWidth, buttonHeight, "Resume");
    settings = new Button(midX, midY + 50, buttonWidth, buttonHeight, "Settings");
    quit = new Button(midX, midY + 150, buttonWidth, buttonHeight, "Quit");
}

void PauseMenu::ButtonDraw() {
    resume->Draw();
    settings->Draw();
    quit->Draw();
}

void PauseMenu::HandleInput() {
    if (resume->IsClicked()) {

        SceneManager::GetInstance()->ChangeScenes(Scenes::GAME_SCENE);
    }

    if (settings->IsClicked()) {

        SceneManager::GetInstance()->ChangeScenes(Scenes::SETTINGS_SCENE);
    }

    if (quit->IsClicked()) {
        // 1. Clean up all game objects
        game->CleanUpGame();

        // 2. Stop music
        SoundManager::GetInstance()->stopBGM();

        // 3. Switch to main menu scene
        SceneManager::GetInstance()->ChangeScenes(Scenes::MAIN_MENU_SCENE);
    }
}

void PauseMenu::Exit() {
    if (resume) { delete resume; resume = nullptr; }
    if (settings) { delete settings; settings = nullptr; }
    if (quit) { delete quit; quit = nullptr; }
}

void PauseMenuInit() {
    Button::LoadResources();
    pauseMenu.ButtonInit();
}

void PauseMenuUpdate() {
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
    CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f,
        CP_System_GetWindowWidth(), CP_System_GetWindowHeight());

    pauseMenu.ButtonDraw();
    pauseMenu.HandleInput();
}

void PauseMenuExit() {
    pauseMenu.Exit();
    Button::FreeResources();
}
