#pragma once
#include "SingletonTemplate.h"
#include <map>
#include <vector>
#include <string>
#include "cprocessing.h"

enum SFX_TYPE
{
	NONE_SFX = 0,
	TEST_SFX = 1,
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
	static const char* SFX_ASSETS_FILE_PATH;
	static const char* BGM_ASSETS_FILE_PATH;

	std::map<SFX_TYPE, CP_Sound> sfxMap;
	std::map<BGM_TYPE, CP_Sound> bgmMap;

	std::vector<SFX_TYPE> sfxTypeVector;
	std::vector<BGM_TYPE> bgmTypeVector;

	std::string getSFXFilePath(SFX_TYPE sfxType);
	std::string getBGMFilePath(BGM_TYPE bgmType);
	void loadAllSounds(void);

protected:
	SoundManager();

public:
	void playSFX(SFX_TYPE sfxType);
	void playBGM(BGM_TYPE bgmType);

	void stopBGM(void);

	void freeAllSounds(void);
};