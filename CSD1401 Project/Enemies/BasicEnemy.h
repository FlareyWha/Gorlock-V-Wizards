/*!
@file       BasicEnemy.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains declarations of functions related to the basic enemy
*//*_______________________________________________________________________*/

#pragma once
#include "BaseEnemy.h"

class BasicEnemy : public BaseEnemy
{
public:
	// Constructor
	BasicEnemy(CP_Vector location);

	// Destructor
	~BasicEnemy();
};

