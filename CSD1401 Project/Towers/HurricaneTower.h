#pragma once
#include "BaseTower.h"
#include "cprocessing.h"
class HurricaneTower : public virtual BaseTower
{
public:
	HurricaneTower(CP_Vector position);
	~HurricaneTower();
};

