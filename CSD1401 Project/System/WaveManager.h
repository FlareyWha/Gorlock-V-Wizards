#pragma once
#include "cprocessing.h"
#include "../Enemies/BaseEnemy.h"
#include "../Enemies/BasicEnemy.h"
#include "../Enemies/SpeedsterEnemy.h"
#include "../Enemies/TankEnemy.h"
#include "../Enemies/BossEnemy.h"

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
	int waveId = 11;
	float spawnCooldown = 1.f, basicCooldown = 0.5f, speedCooldown = 0.25f, tankCooldown = 1.f;
	bool waveInProgress = false;
	bool bossSpawned = false;

public:
	WaveManager(CP_Vector spawnLocation);
	~WaveManager();
	void Update(std::vector<BaseEnemy*>* enemyList);
	void ReadWaveFile(std::ifstream *file, CP_Vector spawnLocation);
	void SpawnWave(CP_Vector spawnLocation);
	bool GetWaveInProgress(void);
};

