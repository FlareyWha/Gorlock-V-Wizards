#pragma once
#include <string>
#include <fstream>
#include <map>

struct WaveInfo
{
	int enemiesList[3] = { 0 };
};

class WaveManager
{
private:
	std::string const fileName = "Assets/waves.txt";
	std::map<int, WaveInfo> waveMap;
public:
	WaveManager();
	~WaveManager();
	void ReadWaveFile(std::ifstream *file);
};

