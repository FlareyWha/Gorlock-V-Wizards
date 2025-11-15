#include "WaveManager.h"

#include <iostream>

WaveManager::WaveManager(CP_Vector spawnLocation)
{
	std::ifstream file(fileName);

	ReadWaveFile(&file, spawnLocation);

	file.close();
}

WaveManager::~WaveManager()
{
	delete enemyQueue;
}

void WaveManager::Update(std::vector<BaseEnemy*>* enemyList)
{
	spawnCooldown -= 1.f * CP_System_GetDt();

	if (!enemyQueue->empty() && spawnCooldown <= 0.f)
	{
		enemyList->push_back(enemyQueue->front());
		switch (enemyQueue->front()->GetEnemyType())
		{
		case EnemyType::BASIC:
			spawnCooldown = basicCooldown;
			break;
		case EnemyType::SPEEDSTER:
			spawnCooldown = speedCooldown;
			break;
		case EnemyType::TANK:
			spawnCooldown = tankCooldown;
			break;
		}
		enemyQueue->pop();
	}
	else if (enemyQueue->empty())
		waveInProgress = false;
}

void WaveManager::ReadWaveFile(std::ifstream *file, CP_Vector spawnLocation)
{
	std::string buffer;
	while (std::getline(*file, buffer))
	{
		int waveNo = std::stoi(buffer.substr(0, buffer.find(':')));
		buffer.erase(0, buffer.find(':') + 1);
		WaveInfo info;
		while (!buffer.empty())
		{
			std::string enemiesInfo;
			if (buffer.find(',') == std::string::npos)
			{
				enemiesInfo = buffer;
				buffer.clear();
			}
			else
			{
				enemiesInfo = buffer.substr(0, buffer.find(','));
				buffer.erase(0, buffer.find(',') + 1);
			}
			int noOfEnemies = std::stoi(enemiesInfo.substr(0, enemiesInfo.length() - 1));
			enemiesInfo.erase(0, enemiesInfo.length() - 1);
			char enemyType = enemiesInfo.at(0);
			for (int i = 0; i < noOfEnemies; ++i)
			{
				switch (enemyType)
				{
				case 'B':
					info.waveQueue->push(new BasicEnemy(spawnLocation));
					break;
				case 'S':
					info.waveQueue->push(new SpeedsterEnemy(spawnLocation));
					break;
				case 'T':
					info.waveQueue->push(new TankEnemy(spawnLocation));
					break;
				}
			}
		}
		waveMap.insert(std::pair<int, WaveInfo>(waveNo, info));
	}
}

void WaveManager::SpawnWave(CP_Vector spawnLocation)
{
	if (waveInProgress) return;
	if (waveId > waveMap.size())
	{
		if (bossSpawned) return;

		enemyQueue->push(new BossEnemy(spawnLocation));
		bossSpawned = true;
		return;
	}

	WaveInfo info = waveMap.at(waveId++);
	enemyQueue = info.waveQueue;
	waveInProgress = true;
}

bool WaveManager::GetWaveInProgress(void)
{
	return waveInProgress;
}
