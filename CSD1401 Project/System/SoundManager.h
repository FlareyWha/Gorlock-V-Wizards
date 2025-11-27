/*!
@file       SoundManager.h
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@co-author	Tat Yang Tai Bryson (t.yangtatbryson)
@brief      This file contains declaration of functions and variables
			used for the SoundManager class
*//*_______________________________________________________________________*/

#pragma once
#include "SingletonTemplate.h"
#include <map>
#include <vector>
#include <string>
#include "cprocessing.h"
#include "SettingsManager.h"

enum SFX_TYPE
{
	NONE_SFX = 0,
	TOWER_PLACE_SFX,
	TOWER_MERGE_SFX,
	ENEMY_BASIC_DEATH_SFX,
	ENEMY_SPEEDSTER_DEATH_SFX,
	ENEMY_TANK_DEATH_SFX,
	ENEMY_BOSS_DEATH_1_SFX,
	ENEMY_BOSS_DEATH_2_SFX,
	TOWER_WIND_ATTACK_SFX,
	TOWER_FIRE_ATTACK_SFX,
	TOWER_LIGHTNING_ATTACK_SFX,
	TOWER_LAVA_ATTACK_SFX,
	TOWER_ICE_ATTACK_SFX,
	TOWER_FREEZE_ATTACK_SFX,
	GAME_WIN_SFX,
	GAME_LOSE_SFX,
	TOTAL_SOUND,
};

enum BGM_TYPE
{
	NONE_BGM = 0,
	MAIN_MENU_BGM,
	GAME_00_BGM,
	GAME_01_BGM,
	GAME_02_BGM,
	TOTAL_BGM,
};

class SoundManager : public SingletonTemplate<SoundManager>
{
	friend class SingletonTemplate<SoundManager>;

private:
	SettingsManager* settingsManager;

	static const char* SFX_ASSETS_FILE_PATH;
	static const char* BGM_ASSETS_FILE_PATH;

	std::map<SFX_TYPE, CP_Sound> sfxMap;
	std::map<BGM_TYPE, CP_Sound> bgmMap;

	std::vector<SFX_TYPE> sfxTypeVector;
	std::vector<BGM_TYPE> bgmTypeVector;

	std::string getSFXFilePath(SFX_TYPE sfxType);
	std::string getBGMFilePath(BGM_TYPE bgmType);
	void loadAllSounds(void);

	float timer;
	float bgm_00_length, bgm_01_length;
	BGM_TYPE currentBgm, nextBgmInQueue = NONE_BGM;

protected:
	SoundManager();

public:
	void Update(void);

	void playSFX(SFX_TYPE sfxType);
	void playBGM(BGM_TYPE bgmType);
	void queueNextBGM(BGM_TYPE bgmType);

	void stopBGM(void);

	void refreshBGMVolume(float bgmVolume);
	void refreshSFXVolume(float sfxVolume);

	void freeAllSounds(void);
};