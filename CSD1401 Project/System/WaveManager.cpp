#include "WaveManager.h"
#include <iostream>

WaveManager::WaveManager()
{
	std::ifstream file(fileName);

	ReadWaveFile(&file);

	file.close();
}

WaveManager::~WaveManager()
{
}

void WaveManager::ReadWaveFile(std::ifstream *file)
{
	std::string buffer;
	while (std::getline(*file, buffer))
	{
		int waveNo = std::stoi(buffer.substr(0, buffer.find(':')));
		buffer.erase(0, buffer.find(':') + 1);
		WaveInfo info;
		for (int i = 0; i < (sizeof(info.enemiesList) / sizeof(info.enemiesList[0])); ++i)
		{
			info.enemiesList[i] = std::stoi(buffer.substr(0, buffer.find(',')));
			buffer.erase(0, buffer.find(',') + 1);
		}
		waveMap.insert(std::pair<int, WaveInfo>(waveNo, info));
	}
}
