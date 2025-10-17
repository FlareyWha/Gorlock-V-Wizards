#include "SettingsManager.h"
#include "cprocessing.h"

int SettingsManager::getSFXVolume(void)
{
	return sfxVolume;
}

float SettingsManager::getSFXVolumeLerp(void)
{
	float volumeFloat = CP_Math_LerpFloat(0.0f, 100.0f, sfxVolume);
	return volumeFloat;
}

void SettingsManager::setSFXVolume(int newVolume)
{
	sfxVolume = newVolume;
}

int SettingsManager::getBGMVolume(void)
{
	return bgmVolume;
}

float SettingsManager::getBGMVolumeLerp(void)
{
	float volumeFloat = CP_Math_LerpFloat(0.0f, 100.0f, bgmVolume);
	return volumeFloat;
}

void SettingsManager::setBGMVolume(int newVolume)
{
	bgmVolume = newVolume;
}
