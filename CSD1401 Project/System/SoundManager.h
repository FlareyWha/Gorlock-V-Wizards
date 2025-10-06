#pragma once
#include "SingletonTemplate.h"
#include <map>
#include <vector>
#include <string>
#include "cprocessing.h"

enum SOUND_TYPE
{
	NONE_SOUND = 0,
	TEST_SOUND = 1,
	TOTAL_SOUND,
};

enum BGM_TYPE
{
	NONE_BGM = 0,
	TEST_BGM = 1,
	TOTAL_BGM,
};

class SoundManager : public SingletonTemplate<SoundManager>
{
	friend class SingletonTemplate<SoundManager>;

private:
	static const char* SOUND_ASSETS_FILE_PATH;
	static const char* BGM_ASSETS_FILE_PATH;

	std::map<SOUND_TYPE, CP_Sound> soundMap;
	std::map<BGM_TYPE, CP_Sound> bgmMap;

	std::vector<SOUND_TYPE> soundTypeVector;
	std::vector<BGM_TYPE> bgmTypeVector;

	std::string getSoundFilePath(SOUND_TYPE soundType);
	std::string getBGMFilePath(BGM_TYPE soundType);
	void loadAllSounds(void);

public:
	bool playSound(SOUND_TYPE soundType);
	bool playBGM(BGM_TYPE bgmType);

	bool stopBGM();

	void freeAllSounds(void);
};