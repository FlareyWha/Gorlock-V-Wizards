#pragma once
#include "BaseEnemy.h"
class SpeedsterEnemy : public BaseEnemy
{
public:
	SpeedsterEnemy(CP_Vector location);
	SpeedsterEnemy(CP_Vector location, float speed);
	~SpeedsterEnemy();
};

