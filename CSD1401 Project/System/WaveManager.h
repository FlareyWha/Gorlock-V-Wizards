/*!
@file       WaveManager.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains declarations of functions related to Wave management
*//*_______________________________________________________________________*/

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
	int waveId = 1, maxWaves = 10;
	float spawnCooldown = 1.f, basicCooldown = 0.5f, speedCooldown = 0.25f, tankCooldown = 1.f;
	bool waveInProgress = false;
	bool bossSpawned = false;

public:
	// Constructor
	WaveManager(CP_Vector spawnLocation);
	// Destructor
	~WaveManager();

	/**
	@brief Update wavemanager related timers
	@param enemyList List of enemies
	@return void
	*/
	void Update(std::vector<BaseEnemy*>* enemyList);
	/**
	@brief Init wave info from a text file
	@param file File to read from
	@param spawnLocation Location for enemies to spawn
	@return void
	*/
	void ReadWaveFile(std::ifstream *file, CP_Vector spawnLocation);
	/**
	@brief Spawn the next wave
	@param spawnLocation Location for enemies to spawn
	@return void
	*/
	void SpawnWave(CP_Vector spawnLocation);
	bool GetWaveInProgress(void);
	int getWaveId(void);
	int getMaxWaves(void);
};

