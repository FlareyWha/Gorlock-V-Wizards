/*!
@file       Map.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains declaration of functions and variables
			used for the SettingsManager class
*//*_______________________________________________________________________*/

#pragma once
#include "SingletonTemplate.h"

class SettingsManager : public SingletonTemplate<SettingsManager>
{
	friend class SingletonTemplate<SettingsManager>;

private:

	//Value from 0-100
	int sfxVolume = 100;
	int bgmVolume = 100;

public:

	int getSFXVolume(void);
	float getSFXVolumeLerp(void);
	void setSFXVolume(int newVolume);
	int getBGMVolume(void);
	float getBGMVolumeLerp(void);
	void setBGMVolume(int newVolume);
};