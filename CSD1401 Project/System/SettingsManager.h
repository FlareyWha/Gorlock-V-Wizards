/*!
@file       SettingsManager.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains declaration of functions and variables
			used for the SettingsManager class
*//*_______________________________________________________________________*/

#pragma once
#include "SingletonTemplate.h"
#include <string>

class SettingsManager : public SingletonTemplate<SettingsManager>
{
	friend class SingletonTemplate<SettingsManager>;

private:
	std::string const bgmFile = "Assets/Settings/bgm.txt";
	std::string const sfxFile = "Assets/Settings/sfx.txt";

	//Value from 0-100
	float sfxVolume = 100;
	float bgmVolume = 100;

public:

	int getSFXVolume(void);
	float getSFXVolumeLerp(void);
	void setSFXVolume(int newVolume);
	int getBGMVolume(void);
	float getBGMVolumeLerp(void);
	void setBGMVolume(int newVolume);

	void readVolumeSettings(void);
};