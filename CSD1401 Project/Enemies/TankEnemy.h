/*!
@file       TankEnemy.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains declarations of functions related to the tank enemy
*//*_______________________________________________________________________*/

#pragma once
#include "BaseEnemy.h"

class TankEnemy : public BaseEnemy
{
public:
	// Constructor
	TankEnemy(CP_Vector location);

	// Destructor
	~TankEnemy();
};

