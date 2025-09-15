/*!
@file       Singleton.cpp
@author     Tai Yang Tat Bryson (t.yangtatbryson)
@brief      This file contains functions to create a Singleton Pattern
*//*_______________________________________________________________________*/

#include "Singleton.h"

Singleton* Singleton::INSTANCE = nullptr;

/*!
@brief      Gets the Singleton Instance

This function creates a Singleton instance if not already existing
and returns the instance.

@param      void
@return     Singleton*
*//*______________________________________________________________*/
Singleton* Singleton::getInstance()
{
	if (INSTANCE == nullptr)
		INSTANCE = new Singleton();

	return INSTANCE;
}
