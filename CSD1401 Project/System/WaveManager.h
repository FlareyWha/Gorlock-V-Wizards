#pragma once
#include "cprocessing.h"
#include "../../Enemies/BaseEnemy.h"
#include "../../Enemies/BasicEnemy.h"
#include "../../Enemies/SpeedsterEnemy.h"
#include "../../Enemies/TankEnemy.h"

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <queue>

struct WaveInfo
{
	std::queue<BaseEnemy*>* waveQueue = new std::queue<BaseEnemy*>();
};

class WaveManager
{
private:
	std::string const fileName = "Assets/waves.txt";
	std::map<int, WaveInfo> waveMap;
	std::queue<BaseEnemy*>* enemyQueue = new std::queue<BaseEnemy*>();
	int waveId = 1;
	float spawnCooldown = 1.f, maxSpawnCooldown = 1.f;
public:
	WaveManager(CP_Vector spawnLocation);
	~WaveManager();
	void Update(std::vector<BaseEnemy*>* enemyList);
	void ReadWaveFile(std::ifstream *file, CP_Vector spawnLocation);
	void SpawnWave(CP_Vector spawnLocation);
};

