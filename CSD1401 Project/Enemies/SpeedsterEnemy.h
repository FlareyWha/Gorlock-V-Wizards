/*!
@file       SpeedsterEnemy.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains declarations of functions related to the speedster enemy
*//*_______________________________________________________________________*/

#pragma once
#include "BaseEnemy.h"
class SpeedsterEnemy : public BaseEnemy
{
public:
	// Constructor(s)
	SpeedsterEnemy(CP_Vector location);
	SpeedsterEnemy(CP_Vector location, float speed);

	// Destructor
	~SpeedsterEnemy();
};

