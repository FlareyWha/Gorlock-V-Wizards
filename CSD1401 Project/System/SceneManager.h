/*!
@file       SceneManager.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains helper functions related to Scene management
*//*_______________________________________________________________________*/

#pragma once
#include "SingletonTemplate.h"

enum Scenes
{
	MAIN_MENU_SCENE = 0,
	GAME_SCENE,
	SETTINGS_SCENE,
	MAP_EDITOR_SCENE,
	PAUSE_MENU_SCENE
};

class SceneManager : public SingletonTemplate<SceneManager>
{
	friend class SingletonTemplate<SceneManager>;
private:
	Scenes currentScene;
	Scenes previousScene;
public:
	void ChangeScenes(Scenes scene);
	Scenes GetPreviousScene() const { return previousScene; }
	Scenes GetCurrentScene() const { return currentScene; }
};
