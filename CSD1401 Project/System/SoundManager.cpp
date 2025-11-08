/*!
@file       SoundManager.cpp
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains definitions of functions 
			used for the SoundManager class
*//*_______________________________________________________________________*/

#include "SoundManager.h"
#include "cprocessing.h"
#include "SettingsManager.h"

const char* SoundManager::SFX_ASSETS_FILE_PATH = "Assets/Sounds/SFX/";
const char* SoundManager::BGM_ASSETS_FILE_PATH = "Assets/Sounds/BGM/";

/*!
@brief Constructor. Makes it load all sounds
*//*______________________________________________________________*/
SoundManager::SoundManager()
{
	settingsManager = SettingsManager::GetInstance();
	loadAllSounds();
	timer = 0.f;
	bgm_00_length = 24.f;
	bgm_00_length = 22.f;
}

void SoundManager::Update(void)
{
	timer += CP_System_GetDt();

	if (nextBgmInQueue == NONE_BGM) return;
	
	switch (currentBgm)
	{
	case GAME_00_BGM:
		if (timer >= bgm_00_length)
		{
			stopBGM();
			playBGM(nextBgmInQueue);
			nextBgmInQueue = NONE_BGM;
		}
		break;
	case GAME_01_BGM:
		if (timer >= bgm_01_length)
		{
			stopBGM();
			playBGM(nextBgmInQueue);
			nextBgmInQueue = NONE_BGM;
		}
		break;
	}
}

/*!
@brief	Gets the sfx file path based on the sfxType of the sfx
@param	SFX_TYPE sfxType - type of sfx based off the enum SFX_TYPE
@return string - filePath of the file to get
*//*______________________________________________________________*/
std::string SoundManager::getSFXFilePath(SFX_TYPE sfxType)
{
	std::string filePath = SFX_ASSETS_FILE_PATH;

	switch (sfxType)
	{
	case TEST_SFX:
		filePath += "duck-toy-sound.mp3";
		break;
	case TOWER_PLACE_SFX:
		filePath += "tower_place.wav";
		break;
	case TOWER_MERGE_SFX:
		filePath += "merge.wav";
		break;
	case ENEMY_BASIC_DEATH_SFX:
		filePath += "basic_death.wav";
		break;
	case ENEMY_SPEEDSTER_DEATH_SFX:
		filePath += "plane_death.wav";
		break;
	case ENEMY_TANK_DEATH_SFX:
		filePath += "tank_death.wav";
		break;
	case TOWER_WIND_ATTACK_SFX:
		filePath += "wind_attack.wav";
		break;
	default:
		break;
	}

	return filePath;
}

/*!
@brief	Gets the bgm file path based on the bgmType of the bgm
@param	BGM_TYPE bgmType - type of bgm based off the enum BGM_TYPE
@return string - filePath of the file to get
*//*______________________________________________________________*/
std::string SoundManager::getBGMFilePath(BGM_TYPE bgmType)
{
	std::string filePath = BGM_ASSETS_FILE_PATH;

	switch (bgmType)
	{
	case TEST_BGM:
		filePath += "mambo.mp3";
		break;
	case MAIN_MENU_BGM:
		filePath += "music_main.wav";
		break;
	case GAME_00_BGM:
		filePath += "music_00.wav";
		break;
	case GAME_01_BGM:
		filePath += "music_01.wav";
		break;
	default:
		break;
	}

	return filePath;
}

/*!
@brief	Load all sfx and bgm and inserts them into their respective map
@param	void
@return void
*//*______________________________________________________________*/
void SoundManager::loadAllSounds(void)
{
	sfxTypeVector = { TEST_SFX, TOWER_PLACE_SFX, TOWER_MERGE_SFX, ENEMY_BASIC_DEATH_SFX, ENEMY_SPEEDSTER_DEATH_SFX, ENEMY_TANK_DEATH_SFX,
					TOWER_WIND_ATTACK_SFX };
	bgmTypeVector = { TEST_BGM, MAIN_MENU_BGM, GAME_00_BGM, GAME_01_BGM };

	for (int i = 0; i < sfxTypeVector.size(); i++)
	{
		CP_Sound tempSFX = CP_Sound_Load(getSFXFilePath(sfxTypeVector[i]).c_str());
		sfxMap.insert({ sfxTypeVector[i], tempSFX });
	}

	for (int i = 0; i < bgmTypeVector.size(); i++)
	{
		CP_Sound tempBGM = CP_Sound_LoadMusic(getBGMFilePath(bgmTypeVector[i]).c_str());
		bgmMap.insert({ bgmTypeVector[i], tempBGM });
	}
}

/*!
@brief	Plays sfx based on sfxType and sfxVolume. Puts all SFX into CP_SOUND_GROUP_1
@param	SFX_TYPE sfxType - type of sfx based off the enum SFX_TYPE
@return void
*//*______________________________________________________________*/
void SoundManager::playSFX(SFX_TYPE sfxType)
{
	CP_Sound_PlayAdvanced(sfxMap[sfxType], settingsManager->getSFXVolumeLerp(), 1.0f, FALSE, CP_SOUND_GROUP_1);
}

/*!
@brief	Plays bgm based on bgmType and bgmVolume. Puts all bgm into CP_SOUND_GROUP_0
@param	BGM_TYPE bgmType - type of bgm based off the enum BGM_TYPE
@return void
*//*______________________________________________________________*/
void SoundManager::playBGM(BGM_TYPE bgmType)
{
	timer = 0.f;
	currentBgm = bgmType;
	CP_Sound_PlayAdvanced(bgmMap[bgmType], settingsManager->getBGMVolumeLerp(), 1.0f, TRUE, CP_SOUND_GROUP_0);
}

void SoundManager::queueNextBGM(BGM_TYPE bgmType)
{
	nextBgmInQueue = bgmType;
}

/*!
@brief	Stops bgm being played using CP_Sound_StopGroup with CP_SOUND_GROUP_0
		as argument
@param	void
@return void
*//*______________________________________________________________*/
void SoundManager::stopBGM(void)
{
	CP_Sound_StopGroup(CP_SOUND_GROUP_0);
}

void SoundManager::refreshBGMVolume(float bgmVolume)
{

	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_0, bgmVolume);
}

void SoundManager::refreshSFXVolume(float sfxVolume)
{
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_1, sfxVolume);
}

/*!
@brief	Frees all sounds from maps, and clears all vectors and maps.
@param	void
@return void
*//*______________________________________________________________*/
void SoundManager::freeAllSounds(void)
{
	for (int i = 0; i < sfxTypeVector.size(); i++)
	{
		CP_Sound_Free(sfxMap[sfxTypeVector[i]]);
	}

	for (int i = 0; i < bgmTypeVector.size(); i++)
	{
		CP_Sound_Free(bgmMap[bgmTypeVector[i]]);
	}

	sfxMap.clear();
	bgmMap.clear();
	sfxTypeVector.clear();
	bgmTypeVector.clear();
}
