#pragma once
#include "BaseEnemy.h"

class BossEnemy : public BaseEnemy
{
public:
	BossEnemy(CP_Vector location);
	void Render(void) override;
	~BossEnemy();
};

