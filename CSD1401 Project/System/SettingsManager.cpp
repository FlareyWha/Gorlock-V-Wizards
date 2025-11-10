/*!
@file       SettingsManager.cpp
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains definitions of functions
			used for the SettingsManager class
*//*_______________________________________________________________________*/

#include "SettingsManager.h"
#include "cprocessing.h"
#include <fstream>
#include <sstream>

/*!
@brief	Gets the SFX volume and returns it
@param	void
@return int - the sfxVolume
*//*______________________________________________________________*/
int SettingsManager::getSFXVolume(void)
{
	return sfxVolume;
}

/*!
@brief	Gets the SFX volume in lerped float from (0.0f to 1.0f) and returns it
@param	void
@return float - the sfxVolume in lerped float form
*//*______________________________________________________________*/
float SettingsManager::getSFXVolumeLerp(void)
{
	float volumeFloat = sfxVolume / 100.f;
	return volumeFloat;
}

/*!
@brief	Sets a new SFX volume
@param	int newVolume - the new volume to set
@return void
*//*______________________________________________________________*/
void SettingsManager::setSFXVolume(int newVolume)
{
	std::ofstream file(sfxFile);
	file << newVolume << "\n";

	sfxVolume = newVolume;
	file.close();
}

/*!
@brief	Gets the BGM volume and returns it
@param	void
@return int - the bgmVolume
*//*______________________________________________________________*/
int SettingsManager::getBGMVolume(void)
{
	return bgmVolume;
}

/*!
@brief	Gets the BGM volume in lerped float from (0.0f to 1.0f) and returns it
@param	void
@return float - the bgmVolume in lerped float form
*//*______________________________________________________________*/
float SettingsManager::getBGMVolumeLerp(void)
{
	//float volumeFloat = CP_Math_LerpFloat(0.0f, 100.0f, bgmVolume);

	float volumeFloat = bgmVolume / 100.f;
	return volumeFloat;
}

/*!
@brief	Sets a new BGM volume
@param	int newVolume - the new volume to set
@return void
*//*______________________________________________________________*/
void SettingsManager::setBGMVolume(int newVolume)
{
	std::ofstream file(bgmFile);
	file << newVolume << "\n";

	bgmVolume = newVolume;
	file.close();
}

void SettingsManager::readVolumeSettings(void)
{
	std::ifstream currentBGMFile(bgmFile);
	std::ifstream currentSFXFile(sfxFile);
	
	std::string line;

	getline(currentBGMFile, line);
	std::stringstream bgmSS(line);
	bgmSS >> bgmVolume;

	getline(currentSFXFile, line);
	std::stringstream sfxSS(line);
	sfxSS >> sfxVolume;
}
