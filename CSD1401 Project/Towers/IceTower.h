#pragma once
#include "BaseTower.h"
class IceTower:public BaseTower
{
private:
	std::string towerName = "WindTower";
public:
	IceTower(CP_Vector position);
	~IceTower();
};

