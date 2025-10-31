#pragma once
#include "BaseTower.h"
class LightningTower : public BaseTower
{
private:
	std::string towerName = "LightningTower";
public:
	LightningTower(CP_Vector position);
	~LightningTower();
};

