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
@return float - the sfxVolume
*//*______________________________________________________________*/
float SettingsManager::getSFXVolume(void) const
{
	return sfxVolume;
}

/*!
@brief	Gets the SFX volume in lerped float from (0.0f to 1.0f) and returns it
@param	void
@return float - the sfxVolume in lerped float form
*//*______________________________________________________________*/
float SettingsManager::getSFXVolumeLerp(void) const
{
	float volumeFloat = sfxVolume / 100.f;
	return volumeFloat;
}

/*!
@brief	Sets a new SFX volume and saves it to file
@param	float newVolume - the new volume to set
@return void
*//*______________________________________________________________*/
void SettingsManager::setSFXVolume(float newVolume)
{
	std::ofstream file(sfxFile);
	file << newVolume << "\n";

	sfxVolume = newVolume;
	file.close();
}

/*!
@brief	Gets the BGM volume and returns it
@param	void
@return float - the bgmVolume
*//*______________________________________________________________*/
float SettingsManager::getBGMVolume(void) const
{
	return bgmVolume;
}

/*!
@brief	Gets the BGM volume in lerped float from (0.0f to 1.0f) and returns it
@param	void
@return float - the bgmVolume in lerped float form
*//*______________________________________________________________*/
float SettingsManager::getBGMVolumeLerp(void) const
{
	float volumeFloat = bgmVolume / 100.f;
	return volumeFloat;
}

/*!
@brief	Sets a new BGM volume and saves it to file
@param	float newVolume - the new volume to set
@return void
*//*______________________________________________________________*/
void SettingsManager::setBGMVolume(float newVolume)
{
	std::ofstream file(bgmFile);
	file << newVolume << "\n";

	bgmVolume = newVolume;
	file.close();
}

/*!
@brief	Reads volume settings from files
@param	void
@return void
*//*______________________________________________________________*/
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
