#pragma once
#include "BaseTower.h"
class WindTower : public BaseTower
{
private:
	std::string towerName = "WindTower";
public:
	WindTower(CP_Vector position);
	~WindTower();
};

