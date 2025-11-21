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

	float getSFXVolume(void) const;
	float getSFXVolumeLerp(void) const;
	void setSFXVolume(float newVolume);
	float getBGMVolume(void) const;
	float getBGMVolumeLerp(void) const;
	void setBGMVolume(float newVolume);

	void readVolumeSettings(void);
};