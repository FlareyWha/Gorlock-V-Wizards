#include "SoundManager.h"
#include "cprocessing.h"

const char* SoundManager::SOUND_ASSETS_FILE_PATH = "Assets/Sounds/Sound";
const char* SoundManager::BGM_ASSETS_FILE_PATH = "Assets/Sounds/BGM";


std::string SoundManager::getSoundFilePath(SOUND_TYPE soundType)
{
	std::string filePath = SOUND_ASSETS_FILE_PATH;

	switch (soundType)
	{
	case TEST_SOUND:
		break;

	default:
		break;
	}

	return filePath;
}

std::string SoundManager::getBGMFilePath(BGM_TYPE bgmType)
{
	std::string filePath = BGM_ASSETS_FILE_PATH;

	switch (bgmType)
	{
	case TEST_BGM:
		break;

	default:
		break;
	}

	return filePath;
}

void SoundManager::loadAllSounds(void)
{
	soundTypeVector = { TEST_SOUND };
	bgmTypeVector = { TEST_BGM };

	for (int i = 0; i < soundTypeVector.size(); i++)
	{
		CP_Sound tempSound = CP_Sound_Load(getSoundFilePath(soundTypeVector[i]).c_str());
		soundMap.insert({ soundTypeVector[i], tempSound });
	}

	for (int i = 0; i < bgmTypeVector.size(); i++)
	{
		CP_Sound tempSound = CP_Sound_LoadMusic(getBGMFilePath(bgmTypeVector[i]).c_str());
		bgmMap.insert({ bgmTypeVector[i], tempSound });
	}
}

bool SoundManager::playSound(SOUND_TYPE soundType)
{
	CP_Sound_Play(soundMap[soundType]);

	return true;
}

bool SoundManager::playBGM(BGM_TYPE bgmType)
{
	CP_Sound_PlayMusic(bgmMap[bgmType]);

	return true;
}

void SoundManager::freeAllSounds(void)
{
	for (int i = 0; i < soundTypeVector.size(); i++)
	{
		CP_Sound_Free(soundMap[soundTypeVector[i]]);
	}

	for (int i = 0; i < bgmTypeVector.size(); i++)
	{
		CP_Sound_Free(bgmMap[bgmTypeVector[i]]);
	}

	soundMap.clear();
	bgmMap.clear();
	soundTypeVector.clear();
	bgmMap.clear();
}
