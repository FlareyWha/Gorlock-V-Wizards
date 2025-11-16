/*!
@file       SceneManager.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains helper functions related to Scene management
*//*_______________________________________________________________________*/

#include "SceneManager.h"
#include "cprocessing.h"
#include "../Scenes/MainMenu/NewMainMenu.h"
#include "../Scenes/Game/Game.h"
#include "../Scenes/Settings/Settings.h"
#include "../Scenes/MapEditor/MapEditor.h"
#include "../../Scenes/PauseMenu/PauseMenu.h"

/*!
@brief      Changes the current active scene

This function changes the current active scene based on the scene
in the parameters.

@param      Scenes scene
@return     void
*/
void SceneManager::ChangeScenes(Scenes scene)
{
    previousScene = currentScene;
    currentScene = scene;

    switch (scene)
    {
    case Scenes::MAIN_MENU_SCENE:
        CP_Engine_SetNextGameState(mainMenuInit, mainMenuUpdate, mainMenuExit);
        break;
    case Scenes::GAME_SCENE:
        CP_Engine_SetNextGameState(gameInit, gameUpdate, gameExit);
        break;
    case Scenes::SETTINGS_SCENE:
        CP_Engine_SetNextGameState(settingsInit, settingsUpdate, settingsExit);
        break;
    case Scenes::MAP_EDITOR_SCENE:
        CP_Engine_SetNextGameState(mapEditorInit, mapEditorUpdate, mapEditorExit);
        break;
    case Scenes::PAUSE_MENU_SCENE:
        CP_Engine_SetNextGameState(PauseMenuInit, PauseMenuUpdate, PauseMenuExit);
        break;
    }
}


