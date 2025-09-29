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
	MAP_EDITOR_SCENE
};

class SceneManager : public SingletonTemplate<SceneManager>
{
	friend class SingletonTemplate<SceneManager>;

public:
	void ChangeScenes(Scenes scene);
};
