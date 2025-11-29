#pragma once
#include "BaseEnemy.h"
/*!
@file       BossEnemy.h
@author     Chee Kang(l.cheekang)
@brief      This file contains the declaration of the BossEnemy class
*//*_______________________________________________________________________*/

class BossEnemy : public BaseEnemy
{
public:
	BossEnemy(CP_Vector location);
	void Render(void) override;
	~BossEnemy();
};

