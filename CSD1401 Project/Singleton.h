/*!
@file       Singleton.h
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains functions to create a Singleton Pattern
*//*_______________________________________________________________________*/

#pragma once

class Singleton
{
private:
	static Singleton* INSTANCE;
	Singleton() {};

public:
	static Singleton* getInstance();
};
